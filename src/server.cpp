#include "utils.hpp"
#include <poll.h>
#include <vector>

int main(void) {
    int juno = socket(AF_INET, SOCK_STREAM, 0) ;

    sockaddr_in juno_addr ;
    juno_addr.sin_family = AF_INET ;
    juno_addr.sin_port = htons(8080) ;
    juno_addr.sin_addr.s_addr = INADDR_ANY ;
    bind(juno, (struct sockaddr*) &juno_addr, sizeof(juno_addr)) ;

    listen(juno, 5) ;
    
    // getting the IP
    socklen_t juno_len = sizeof(juno_addr) ;
    getsockname(juno, (struct sockaddr*) &juno_addr, &juno_len) ;
    char ip[INET_ADDRSTRLEN] ;
    inet_ntop(AF_INET, &(juno_addr.sin_addr), ip, INET_ADDRSTRLEN) ;

    std::cout << "IP Address: " << ip << std::endl ;
    std::cout << "Juno is listening on port 8080!" << std::endl ;

    std::vector<pollfd> fds ;
    fds.reserve(5) ; // as of right now I am just setting a limit of 5 users
    pollfd server ;
    server.fd = juno ;
    server.events = POLLIN ;
    fds.push_back(server) ;
    while(true) {
        int timeout = -1 ; // will wait forever
        int res = poll(fds.data(), fds.size(), timeout) ;
        if(res > 0) {
            for(int i = 0 ; i < fds.size() ; i++) {
                if(fds[i].revents & POLLIN) {
                    if(fds[i].fd == juno) {
                        sockaddr_in kiriko_addr ;
                        socklen_t kiriko_len = sizeof(kiriko_addr) ;
                        int kiriko = accept(juno, (struct sockaddr*) &kiriko_addr, &kiriko_len) ;
                        pollfd client ;
                        client.fd = kiriko ;
                        client.events = POLLIN ;
                        fds.push_back(client) ;
                    } else {
                        char str[256] = {0} ;
                        ssize_t b = recv(fds[i].fd, str, sizeof(str), 0) ;
                        if(b <= 0) {
                            close(fds[i].fd) ;
                            fds.erase(fds.begin() + i) ;
                            std::cout << "=> LOG: Client #" << i << " has disconnected" << std::endl ;
                            i-- ;
                        } else {
                            std::cout << "Kiriko #" << i << " says: " << str << std::endl ;
                        }
                    }
                }
            }
        }
    }
    
    close(juno) ;
    return 0 ;
}