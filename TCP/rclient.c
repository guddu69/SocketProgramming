#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>
#include <unistd.h> // IMP added afterwards for mac users
int main(){
    
    // creating socket
    int socket_n = socket(AF_INET, SOCK_STREAM,0);

    // allocating address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // making connection
    int connection = connect(socket_n, (struct sockaddr*) &server_address, sizeof(server_address));

    if (connection == -1){
        printf("Error occured\n");
    }

    // sending message to server
    char smsg[256];
    printf("Enter the message: ");
    fgets(smsg , sizeof(smsg), stdin); // taking input from user
    send(socket_n, smsg, sizeof(smsg), 0 );

    printf("Sending: %s",smsg);

    // receving message from client
    char msg[256];
    recv(socket_n, &msg, sizeof(msg), 0);

    // printing msg
    printf("Recieved: %s", msg);

    // closing socket
    close(socket_n);

    return 0;
}