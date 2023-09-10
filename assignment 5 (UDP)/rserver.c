#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#include <unistd.h> // IMP added afterwards for mac users
#include<string.h> 
#define PORT 8080
int main(){

    // creating socket
    int socket_n = socket(AF_INET, SOCK_DGRAM, 0);

    // defining socket address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    while(1){
        // binding to specific port number and IP
        bind(socket_n, (struct sockaddr*) &server_address, sizeof(server_address));

        struct sockaddr_in client_addr;

        // recieving message from client
        char rmsg[256];
        socklen_t client_n_len = sizeof(client_addr);
        ssize_t bytes_rev = recvfrom(socket_n, rmsg, sizeof(rmsg), 0, (struct sockaddr*)&client_addr, &client_n_len);

        rmsg[bytes_rev] = '\0'; // Null-terminate the received message
        if (strcmp(rmsg, "exit\n")==0){
            break;
        }

        // sending the message
        printf("Reply: ");
        char smsg[256];
        fgets(smsg , sizeof(smsg), stdin); // taking input from user
        ssize_t bytes_sent = sendto(socket_n, smsg, bytes_rev, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
        
        if (strcmp(smsg, "exit\n")==0){
            break;
        }
    }
    // closing sockets
    close(socket_n);

    return 0;

}
