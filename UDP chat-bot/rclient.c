#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>

#include<unistd.h>
#include<netinet/in.h>

#include<string.h>

int main(){

    int socket_n = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in client_address;
    client_address.sin_family = AF_INET;
    client_address.sin_port = htons(8080);
    client_address.sin_addr.s_addr = INADDR_ANY;

    while(1){

        char smsg[256];
        printf("Enter: ");
        fgets(smsg, sizeof(smsg), stdin);
        sendto(socket_n, smsg, sizeof(smsg),0, (struct sockaddr*)&client_address, sizeof(client_address));

        if(strcmp(smsg,"exit\n")==0)
            break;

        char rmsg[256];
        socklen_t len = sizeof(client_address);
        recvfrom(socket_n, rmsg, sizeof(rmsg), 0, (struct sockaddr*)&client_address, &len);
        printf("Server: %s",rmsg);

        if(strcmp(rmsg,"exit\n")==0)
            break;

    }

    close(socket_n);

    return 0;
}
