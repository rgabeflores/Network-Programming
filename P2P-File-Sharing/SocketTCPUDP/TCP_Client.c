// TCP Client program 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <pthread.h>
#include <unistd.h>
#include "Client.h"
#define NUM_THREADS 3
#define PORT 5000 
#define MAXLINE 1024 

int ID = -1;
char* fileList[2] = {"a.txt","b.txt"};

void TCP_CALL()
{
	int sockfd; 
	char buffer[MAXLINE]; 
	char* message = "Hello TCP"; 

	struct sockaddr_in servaddr;



	// Creating socket file descriptor 
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		printf("socket creation failed"); 
		exit(0); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	if (connect(sockfd, (struct sockaddr*)&servaddr, 
							sizeof(servaddr)) < 0) { 
		printf("\n Error : Connect Failed \n"); 
	} 

	memset(buffer, 0, sizeof(buffer)); 
	strcpy(buffer, "Hello Server TCP"); 
	write(sockfd, buffer, sizeof(buffer)); 
	printf("\nMessage from server: "); 
	read(sockfd, buffer, sizeof(buffer)); 
	puts(buffer); 
	close(sockfd);
}

void TCP_SEARCH()
{
	int sockfd; 
	char buffer[MAXLINE]; 
	//char* message = filename; 

	struct sockaddr_in servaddr;



	// Creating socket file descriptor 
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
		printf("socket creation failed"); 
		exit(0); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	if (connect(sockfd, (struct sockaddr*)&servaddr, 
							sizeof(servaddr)) < 0) { 

		printf("\n Error : Connect Failed \n"); 
	} 
	int x = Menu();
	char x1[1];
	char f1[50];
	sprintf(x1, "%f", x);	
	
	if(x==1){

	memset(buffer, 0, sizeof(buffer)); 
	strcpy(buffer, x1); 
	write(sockfd, buffer, sizeof(buffer)); 

	printf("\nEnter filename");
	gets(f1);
	strcpy(buffer,f1);
	write(sockfd, buffer, sizeof(buffer)); 
	
	printf("\nMessage from server: "); 
	read(sockfd, buffer, sizeof(buffer)); 
	puts(buffer); 

	//broadcastSearch(10);
	

	}
	close(sockfd);
}

void UDP_HELLO(){
	
	int selection = 0;
	char fileN[100];

	int sockfd;
	int sockfd_UDP;
	char UDPbuffer[MAXLINE]; 
	struct sockaddr_in servaddr;

	if ((sockfd_UDP = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
		printf("UDP socket creation failed"); 
		exit(0); 
	} 

	char* message1 = "HELLO";
	
	memset(&servaddr, 0, sizeof(servaddr)); 

	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	/*
	sendto(sockfd_UDP, (const char*)message1, strlen(message1), 
		0, (const struct sockaddr*)&servaddr, 
		sizeof(servaddr)); 
	*/

	//selection = Menu();
	if(selection == 2){
		
		printf("\nSearching");
	}
	
	for(;;){
		sleep(60);		
		sendto(sockfd_UDP, (const char*)message1, strlen(message1), 
		0, (const struct sockaddr*)&servaddr, 
		sizeof(servaddr)); 
		
		
	}
	//0, filename
}

void UDP_SEARCH(char* filename){
	

	int sockfd;
	int sockfd_UDP;
	char UDPbuffer[MAXLINE]; 
	struct sockaddr_in servaddr;

	if ((sockfd_UDP = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
		printf("UDP socket creation failed"); 
		exit(0); 
	} 

	char* message1 = filename; 
	
	memset(&servaddr, 0, sizeof(servaddr)); 

	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	sendto(sockfd_UDP, (const char*)message1, strlen(message1), 
		0, (const struct sockaddr*)&servaddr, 
		sizeof(servaddr)); 
}

void UDP_fetch(int clientID_Send, int clientID_Receive, char* filename)
{
	if(ID == clientID_Send)
	{
		for(int i=0;i<(sizeof(fileList)/sizeof(char*));i++)
		{
			if(strcmp(fileList[i],filename)==0)
			{
				printf("\nSending %s to client %d",fileList[i], clientID_Receive);
			}
		}
	}
}

int Menu()
{
	int selection = 0;
	printf("\nEnter your selection:");
	printf("\n1: Search for files");
	printf("\n2: Get a file");
	selection = getchar();
	selection -= '0';
	printf("%d",selection);
	return selection;
}


int main() 
{ 



	int rc;
	int i;
	
	pthread_t thread_array[NUM_THREADS];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	rc = pthread_create(&thread_array[0], NULL, TCP_SEARCH, (void*) NULL);
	rc = pthread_create(&thread_array[1], NULL, UDP_HELLO, (void*) NULL);
	rc = pthread_create(&thread_array[1], NULL, broadcastListen, (void*) NULL);
	
	for(int i = 0;i<3;i++){
		pthread_join(thread_array[i],NULL);
	}

	
	
	 
} 
