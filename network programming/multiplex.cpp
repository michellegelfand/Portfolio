
// Server program 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> //fd_set
#include <unistd.h> 
#include <string.h> // strcmp
#include <iostream>//cout

#define PORT 4550 
#define MAXLINE 1024 

void handleUDP(int fd, struct sockaddr_in* server_addr);
void handleTCP(int fd, struct sockaddr_in* server_addr, fd_set *fdset);
void handleSTDIN(int fd);

int max(int x, int y) 
{ 
    if (x > y) 
        return x; 
    else
        return y; 
} 


void handleUDP(int fd, struct sockaddr_in* server_addr)
{
    char buffer[MAXLINE] = {0}; 
	socklen_t len = sizeof(*server_addr);

	/* recieve */
	recvfrom(fd,buffer,sizeof(buffer),0,
            (struct sockaddr*)server_addr,&len); 
    printf("%s\n", buffer); 
       
	/* reply to sender */
	if (0 == strcmp(buffer, "Ping\n"))
	{
		 sendto(fd,"Pong",strlen("Pong"),0,
            (struct sockaddr*)server_addr,sizeof(*server_addr));
	}
}

void handleTCP(int fd, struct sockaddr_in* server_addr, fd_set *fdset)
{
    char buffer[MAXLINE] = {0};
    int client_sock = 0;
    socklen_t len = 0;


	/* establish new connection */
	client_sock = accept(fd, (struct sockaddr *)server_addr,  
        &len);

	/* recieve message */
    FD_SET(client_sock, fdset);
	recv( client_sock , buffer, MAXLINE, 0); 
 
	/*reply */
	if (0 == strcmp(buffer, "Ping\n"))
	{
		send(client_sock , "Pong" , strlen("Pong")+1 , 0 ); 
	}

}

void handleSTDIN(int fd)
{
	char buffer[MAXLINE] = {0}; 

	/* get message */
	read( fd , buffer, MAXLINE); 
     
	/* reply to user */
	if (0 == strcmp(buffer, "Ping\n"))
	{ 
    	printf("Server : Pong!!!\n");
	}
	else if (0 == strcmp(buffer, "Quit\n"))
	{
		exit(0);
	}

}

int main() 
{ 
    fd_set fdset; 
    int tcpfd = 0;
    int udpfd = 0;
    int nfds = 0; 
    int fd_popped_up = 0;

    char buffer[MAXLINE]; 

    socklen_t len; 

    const int on = 1; 
    struct sockaddr_in cliaddr, servaddr; 
  
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

////////////////////////////////////////////////////
    /* create listening TCP socket */
    
    if(-1 == (tcpfd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        printf("TCP socket failed\n");
        return 1;
    } 
  
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = /* htonl (*/INADDR_ANY/* ) */; 
    servaddr.sin_port = htons(PORT);  

    // binding server addr structure to tcpfd 
    if(-1 == (bind(tcpfd, (struct sockaddr*)&servaddr, sizeof(servaddr))))
    {
        printf("tcp bind failed\n");
        return 1;
    } 
    
    int broadcastPermission = 1;

    if (setsockopt(udpfd, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermission, sizeof(broadcastPermission)) < 0)
	/* {
        printf("Opening UDP port for broadcasts failed.\n");
        return 1;
	} */


    listen(tcpfd, 10); 
////////////////////////////////////////////////////////


    /* create UDP socket */
    udpfd = socket(AF_INET, SOCK_DGRAM, 0); 
    // binding server addr structure to udp sockfd 
    if(-1 == (bind(udpfd, (struct sockaddr*)&servaddr, sizeof(servaddr))))
    {
        printf("udp bind failed");
        return 1;
    }

    

/////////////////////////////////////////////////////////  
   
    // clear the descriptor set 
    FD_ZERO(&fdset); 
  
    // get maxfd , add 1 for array size
    int maxfdp1 = max(tcpfd, udpfd) + 1; 
    
    for (;;) 
    { 
        // push them into array
        FD_ZERO(&fdset);
        FD_SET(tcpfd, &fdset); 
        FD_SET(udpfd, &fdset); 
        FD_SET(STDIN_FILENO, &fdset);

        // select the ready descriptor 
        if( 0 != (fd_popped_up = select(1024, &fdset, NULL, NULL, &tv))) 
        {
            tv.tv_sec = 5;
            tv.tv_usec = 0;

            // IF POPPED UP TCP, HANDLE TCP
            if (FD_ISSET(tcpfd, &fdset)) 
            { 
            /* ++maxfdp1; */
                handleTCP(tcpfd, &servaddr, &fdset);
            } 
            // IF POPPED UP UDP, HANDLE UDP 
            else if (FD_ISSET(udpfd, &fdset)) 
            { 
                handleUDP(udpfd, &servaddr);
            }
            else if(FD_ISSET(STDIN_FILENO, &fdset))
            {
                handleSTDIN(STDIN_FILENO);
            }
            else
            {
                std::cout << "timeout" << std::endl;
                exit(0);
            }
            
            std::cout << std::endl;
        } 
    }
    return 0;
}

