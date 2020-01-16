/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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
	int cliSock;
	struct sockaddr_in clientaddr;

    char input[BUFFER];
    char output[BUFFER];
    int len;
    
    cliSock = socket(AF_INET,SOCK_STREAM,0);//(domain, type , protocol)
    if(cliSock == -1)
    {
        perror("SOCKET failed to create\n");
        exit(-1);
    }
	
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(atoi(argv[2]));
    clientaddr.sin_addr.s_addr = inet_addr(argv[1]);
    bzero(&clientaddr.sin_zero,8);

	if(connect(cliSock, (struct sockaddr*)&clientaddr, sizeof(struct sockaddr_in)) == -1)
	{
	    perror("Connection failed");
	    exit(-1);
	}
	
	
	fgets(input,BUFFER, stdin);
	send(cliSock,input,strlen(input),0);

	len = recv(cliSock, output, BUFFER, 0);
	output[len] ='\0';
	printf("%s\n",output);
	
	close(cliSock);
	
}

