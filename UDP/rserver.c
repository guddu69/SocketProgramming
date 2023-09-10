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

    socklen_t len = sizeof(client_address);

    bind(socket_n, (struct sockaddr*)&server_address, sizeof(server_address));

    char rmsg[256];
    ssize_t brev = recvfrom(socket_n, rmsg, sizeof(rmsg), 0, (struct sockaddr*)&client_address, &len);

    printf("Echo back: %s", rmsg);

    rmsg[brev] = '\0';
    sendto(socket_n, rmsg, brev, 0, (struct sockaddr*)&client_address, sizeof(client_address));

    close(socket_n);

    return 0;

}
