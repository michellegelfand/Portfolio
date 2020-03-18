
#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr
#include <unistd.h>//sleep

int main(int argc , char *argv[])
{
	int sockfd;
	struct sockaddr_in server;
	char message[10] = "Ping";
    char server_reply[10] = {0};
	
	//Create socket
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if (sockfd == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("10.3.0.23");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8888 );

	//Connect to remote server
	if (connect(sockfd , (struct sockaddr *)&server , sizeof(server)) == -1)
	{
		perror("connect failed. Error");
		return 1;
	}

	puts("Connected\n");
	
	//keep communicating with server
	while(1)
	{
		//printf("Send message : %s \n", message);
		//scanf("%s" , message);
		
		//Send some data
		if( send(sockfd , message , strlen(message) , 0) == -1)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sockfd , server_reply , 2000 , 0) == -1)
		{
			puts("recv failed");
			break;
		}
		
		printf("%s \n", server_reply);

        sleep(1);
	}
	
	close(sockfd);
	return 0;
}