/* UDP server - ping pong */

#include<stdio.h>	   /* printf  */
#include<string.h>     /* memset  */
#include<stdlib.h>     /* exit(0) */
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>     /* close */

#define BUFLEN 512	/* Max length of buffer */
#define PORT 8888	/* The port on which to listen for incoming data */

void die(char *s);

int main(void)
{
	struct sockaddr_in si_me, si_other;
	int s;
	int i;
	int slen = sizeof(si_other);
	int recv_len;
	char buf[BUFLEN] = {0};
	char message[BUFLEN] = "Pong";
	
	/* create a UDP socket */
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
	
	/* zero out the structure */
	memset((char *) &si_me, 0, sizeof(si_me));
	
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
	
	/* bind socket to port */
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		die("bind");
	}

	/* keep listening for data */
	while(1)
	{
		fflush(stdout);
		
		/* try to receive some data, this is a blocking call */
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) /*and recieve address of sender to si_other*/
		{
			die("recvfrom()");
		}
		
		/*print details of the client/peer and the data received
		/* printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr),
													 ntohs(si_other.sin_port)); */
		printf("%s\n", buf);
		
		/* now reply the client with the same data */
		if (sendto(s, message, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
		{
			die("sendto()");
		}
	}

	close(s);

	return 0;
}

void die(char *s)
{
	perror(s);
	exit(1);
}

