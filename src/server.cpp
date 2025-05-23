#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>

using namespace std ;

int main(void) {
    // juno is the server
    int juno = socket(AF_INET, SOCK_STREAM, 0) ;

    sockaddr_in sAddr ;
    sAddr.sin_family = AF_INET ;
    sAddr.sin_port = htons(8080) ;
    sAddr.sin_addr.s_addr = INADDR_ANY ;
    bind(juno, (struct sockaddr*) &sAddr, sizeof(sAddr)) ;

    if(listen(juno, 5) == 0) {
        cout << "Juno is listening on port 8080!" << endl ;
    }
    else {
        cout << "Juno is not listening" << endl ;
    }

    int kiriko = accept(juno, nullptr, nullptr) ;
    char str[1024] = {0} ;
    recv(kiriko, str, sizeof(str), 0) ;
    cout << "Kiriko says: " << str << endl ;

    close(juno) ;

    return 0 ;
}