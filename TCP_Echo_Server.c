#include <stdio.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h>
#include <strings.h>
#include <string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define BUFFER 1024
void main(int argc, char **argv)
{
    struct sockaddr_in server;
    struct sockaddr_in client;
    int sock;
    int clisock;
    
    int sockaddr_len = sizeof(struct sockaddr_in);
    
    int data_len;
    char data[BUFFER];
    
    if(sock == socket(AF_INET,SOCK_STREAM,0) == -1)
    {
        perror("SOCKET failed to create\n");
        exit(-1);
    }
    
    server.sin_family = AF_INET;
    server.sin_port= htons(atoi(argv[1]));
    server.sin_addr.s_addr =INADDR_ANY;
    bzero(&server.sin_zero,8);

    if(bind(sock,(struct sockaddr *)&server,sockaddr_len) == -1)    
    {
        perror("Bind failed");
        exit(-1);
    }
    
    if(listen(sock,2)==-1)
    {
        perror("failed to listen\n");
        exit(-1);
    }
    
    if(clisock = accept(sock,(struct sockaddr *)&client, &sockaddr_len) == -1)
    {
        perror("Accept failed");
        exit(-1);
    }
    printf("new client connected from port %d and address %s..\n",ntohs(client.sin_port),inet_ntoa(client.sin_addr));
    
    
    data_len =recv(clisock,data,BUFFER,0);
    if(data_len)
    {
        send(clisock,data,data_len,0);
        data[data_len] ='\0';
        printf("sent message %s",data);
    }
    close(clisock);
    
}