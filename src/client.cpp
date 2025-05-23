#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int main(void) {
    int kiriko = socket(AF_INET, SOCK_STREAM, 0) ;

    sockaddr_in sAddr ;
    sAddr.sin_family = AF_INET ;
    sAddr.sin_port = htons(8080) ;
    sAddr.sin_addr.s_addr = INADDR_ANY ;
    connect(kiriko, (struct sockaddr*) &sAddr, sizeof(sAddr)) ;

    const char* msg = "Let the kitsune guide you!" ;
    send(kiriko, msg, strlen(msg), 0) ;

    close(kiriko) ;

    return 0 ;
}