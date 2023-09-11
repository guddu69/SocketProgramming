#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<unistd.h>
#include<netinet/in.h>

#include<string.h>

int main(){

    int socket_n = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(socket_n, (struct sockaddr*)&server_address, sizeof(server_address));

    while(1){

        char rmsg[256];
        socklen_t len = sizeof(client_address);
        ssize_t bytes_recv = recvfrom(socket_n, rmsg, sizeof(rmsg), 0, (struct sockaddr*)&client_address, &len);

        rmsg[bytes_recv] = '\0';
        printf("Client: %s", rmsg);

        if(strcmp(rmsg, "exit\n")==0)
            break;

        printf("Reply: ");
        char smsg[256];
        fgets(smsg, sizeof(smsg), stdin);
        sendto(socket_n, smsg, bytes_recv, 0, (struct sockaddr*)&client_address, sizeof(client_address));

        if(strcmp(smsg, "exit\n")==0)
            break;

    }

    close(socket_n);

    return 0;

}
