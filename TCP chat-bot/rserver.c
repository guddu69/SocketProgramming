#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<unistd.h>
#include<netinet/in.h>

#include<string.h>
// create -> address -> bind -> listen -> accept -> while -> close
int main(){
    
    // creating socket
    int socket_n = socket(AF_INET, SOCK_STREAM, 0);

    // defining server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // binding socket to port number and IP
    bind(socket_n, (struct sockaddr*)&server_address, sizeof(server_address));
    listen(socket_n, 5);
    int client_n = accept(socket_n, NULL, NULL);

    while(1){

        // RECEVING

        char rmsg[256];
        recv(client_n, &rmsg, sizeof(rmsg), 0);

        printf("CLIENT: %s", rmsg);

        if (strcmp(rmsg, "exit\n")==0){
            printf("EXITING...");
            break;
        }

        // SENDING

        printf("Reply: ");
        char smsg[256];
        fgets(smsg, sizeof(smsg), stdin);
        send(client_n, smsg, sizeof(smsg), 0);
        
        if (strcmp(smsg, "exit\n")==0){
            printf("EXITING...");
            break;
        }

    }

    close(client_n);
    close(socket_n);
    
    return 0;

}
