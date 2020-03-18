#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

void DieWithError(char *errorMessage);  /* External error handling function */

int main(int argc, char *argv[])
{
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    char *broadcastIP;                /* IP broadcast address */
    unsigned short broadcastPort;     /* Server port */
    char *string_to_broadcast;                 /* String to broadcast */
    int broadcastPermission;          /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */

    if (argc < 4)                     /* Test for correct number of parameters */
    //a.out , ip addres , port, string to broadcast
    {
        fprintf(stderr,"Usage:  %s <IP Address> <Port> <Send String>\n", argv[0]);
        exit(1);
    }

    broadcastIP = argv[1];            /* First arg:  broadcast IP address */ 
    broadcastPort = atoi(argv[2]);    /* Second arg:  broadcast port */
    string_to_broadcast = argv[3];             /* Third arg:  string to broadcast */

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");

    /* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &     
        broadcastPermission, sizeof(broadcastPermission)) < 0)
        DieWithError("setsockopt() failed");

    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;     /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);/* Broadcast IP address */
    broadcastAddr.sin_port = htons(broadcastPort);         /* Broadcast port */
    sendStringLen = strlen(string_to_broadcast);  /* Find length of string_to_broadcast */

    for (;;) /* Run forever */
    {  
         /* Broadcast string_to_broadcast in datagram to clients every 3 seconds*/
         if (sendto(sock, string_to_broadcast, sendStringLen, 0,
                    (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
             DieWithError("sendto() sent a different num of B than expected");

         sleep(1);    /* Avoids flooding the network */

        scanf("%s", string_to_broadcast);
        sendStringLen = strlen(string_to_broadcast); 
    } 
    /* NOT REACHED */
}

void DieWithError(char *errorMessage)  /* External error handling function */
{
}

