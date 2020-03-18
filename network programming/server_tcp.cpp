#include<stdio.h>
#include<string.h>	/*strlen*/
#include<sys/socket.h>
#include<arpa/inet.h>	/*inet_addr*/
#include<unistd.h>	/*write*/
#include <unistd.h>/*sleep*/

int main(int argc , char *argv[])
{
	int sockfd , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[10];
	char client_message1[10] = "Pong";
	
	//Create socket
	sockfd = socket(AF_INET , SOCK_STREAM , 0);
	if (sockfd == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	//Bind
	if( bind(sockfd,(struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("bind failed");
		return 1;
	}
	puts("bind done");
	
	//Listen for client
	listen(sockfd , 3);

	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock = accept(sockfd, (struct sockaddr *)&client,
                         (socklen_t*)&c);
	if (client_sock == -1)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
	
	//Receive a message from client
	while( (read_size = recv(client_sock , client_message , 2000 , 0)) != -1 )
	{
        printf("%s\n", client_message);
		//Send the message back to client
		write(client_sock , client_message1 , strlen(client_message1));
    }
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
	
	return 0;
}