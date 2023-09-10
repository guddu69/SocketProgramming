#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<unistd.h>
#include<netinet/in.h>

#include<string.h>
// create -> address -> connect -> while -> close
int main(){
 
    // creating socket
    int socket_n = socket(AF_INET, SOCK_STREAM, 0);

    // defining client address
    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(9002);
    client_address.sin_addr.s_addr = INADDR_ANY;

    // making connection to the servet
    int connection = connect(socket_n, (struct sockaddr*)&client_address, sizeof(client_address));

    if (connection == -1){
        printf("error occured during connection\n");
    }
    
    while(1){

        // SENDING

        char smsg[256];
        printf("Enter msg: ");
        fgets(smsg, sizeof(smsg), stdin);
        send(socket_n, smsg, sizeof(smsg), 0);

        if(strcmp(smsg,"exit\n")==0){
            printf("EXITING...");
            break;
        }

        // RECEVING

        char rmsg[256];
        recv(socket_n, &rmsg, sizeof(rmsg), 0);

        printf("SERVER: %s", rmsg);
        if (strcmp(rmsg, "exit\n")==0){
            printf("EXITING...");
            break;
        }

    }

    close(socket_n);

    return 0;

}
