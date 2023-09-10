#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#include <unistd.h> // IMP added afterwards

int main(){

    // creating socket
    int socket_n = socket(AF_INET, SOCK_STREAM, 0);

    // defining socket address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // binding to specific port number and IP
    bind(socket_n, (struct sockaddr*) &server_address, sizeof(server_address));

    // listining for any connection
    listen(socket_n, 5);

    // accepting the connection
    int client_n = accept(socket_n, NULL, NULL);

    // sending the message
    char msg[256] = "This is msg from server.";
    send(client_n, msg, sizeof(msg),0);

    // closing the socket
    close(socket_n);

    return 0;

}