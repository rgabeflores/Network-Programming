#ifndef CLIENT
#define CLIENT

#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define PORT 65432

void * broadcastSearch(int ID){
	int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    char *broadcastIP;                /* IP broadcast address */
    unsigned short broadcastPort;     /* Server port */
    char *sendString;                 /* String to broadcast */
    int broadcastPermission;          /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */

    broadcastIP = "127.0.0.1";            /* First arg:  broadcast IP address */ 
    broadcastPort = PORT;    /* Second arg:  broadcast port */
    sendString = ID + '0';             /* Third arg:  string to broadcast */

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
       printf("socket() failed");
    }

    /* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, 
          sizeof(broadcastPermission)) < 0)
    {
       printf("setsockeopt() failed");
    }

    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);/* Broadcast IP address */
    broadcastAddr.sin_port = htons(broadcastPort);         /* Broadcast port */

    sendStringLen = strlen(sendString);  /* Find length of sendString */
   
    for (int i = 0; i < 5; i++) /* Run forever */
    {
         /* Broadcast sendString in datagram to clients every 3 seconds*/
         if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) 
               &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
         {
             printf("sendto() sent a different number of bytes than expected");
         }

        sleep(3);   /* Avoids flooding the network */
    }
}

void * broadcastListen(){
	int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast Address */
    unsigned short broadcastPort;     /* Port */
    char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
    int recvStringLen;                /* Length of received string */

    broadcastPort = PORT;   /* First arg: broadcast port */

    /* Construct bind structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* Any incoming interface */

    broadcastAddr.sin_port = htons(broadcastPort);      /* Broadcast port */

   for(;;)
    {
   
       if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
       {
           printf("Socket() failed\n");
       }
 
       /* Bind to the broadcast port */
       if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
       {
        	close(sock);
        	continue;
       }
 

       /* Receive a single datagram from the server */
       if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
       {
          printf("recvfrom() failed");
       }
       
       recvString[recvStringLen] = '\0';
       printf("Received: %s\n", recvString);    /* Print the received string */
       close(sock);
       sleep(5);
   }
}

#endif