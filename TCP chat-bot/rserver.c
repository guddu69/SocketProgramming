#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<netinet/in.h>

#include <unistd.h> // IMP added afterwards for mac users
#include <string.h>
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
    listen(socket_n, 5); // listining for any connection

    // accepting the connection
    int client_n = accept(socket_n, NULL, NULL);

   while (1){
        // recieving message from client
        char rmsg[256];
        recv(client_n, &rmsg, sizeof(rmsg), 0);

        printf("Msg from client: %s",rmsg);

        if (strcmp(rmsg, "exit\n")==0)
        {
            break;
        }

        char smsg[256];
        printf("Reply: ");
        fgets(smsg , sizeof(smsg), stdin); // taking input from user
        send(client_n, smsg, sizeof(smsg), 0 );

        if (strcmp(smsg, "exit\n")==0)
        {
            break;
        }

   }
   

    // closing both sockets
    close(client_n);
    close(socket_n);

    return 0;

}