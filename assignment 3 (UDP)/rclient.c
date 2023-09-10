#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include <unistd.h> // IMP added afterwards for mac users
#include <string.h>
#define PORT 8080
int main(){
    
    // creating socket
    int socket_n = socket(AF_INET, SOCK_DGRAM, 0);

    // allocating address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // sending message to server
    char smsg[256];
    printf("Enter the message: ");
    fgets(smsg , sizeof(smsg), stdin); // taking input from user
    ssize_t bytes_sent = sendto(socket_n, smsg, strlen(smsg), 0, (struct sockaddr*)&server_address, sizeof(server_address));

    printf("Sending: %s",smsg);

    // receving message from client
    char rmsg[256];
    socklen_t server_addr_len = sizeof(server_address);
    ssize_t bytes_received = recvfrom(socket_n, rmsg, sizeof(rmsg), 0, (struct sockaddr*)&server_address, &server_addr_len);


    // Null-terminate the received message
    rmsg[bytes_received] = '\0';

    // printing msg
    printf("Recieved: %s\n", rmsg);

    // closing socket
    close(socket_n);

    return 0;
}