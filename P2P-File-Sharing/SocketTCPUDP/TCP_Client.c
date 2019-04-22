// TCP Client program 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 2
#define PORT 5000 
#define MAXLINE 1024 

void TCP_CALL()
{
	int sockfd; 
	char buffer[MAXLINE]; 
	char* message = "Hello Server"; 

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
	strcpy(buffer, "Hello Server"); 
	write(sockfd, buffer, sizeof(buffer)); 
	printf("Message from server: "); 
	read(sockfd, buffer, sizeof(buffer)); 
	puts(buffer); 
	close(sockfd);
}

void UDP_CALL(){
	

	int sockfd;
	int sockfd_UDP;
	char UDPbuffer[MAXLINE]; 
	struct sockaddr_in servaddr;

	if ((sockfd_UDP = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
		printf("UDP socket creation failed"); 
		exit(0); 
	} 

	char* message1 = "Hello Server UDP"; 
	
	memset(&servaddr, 0, sizeof(servaddr)); 

	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	sendto(sockfd_UDP, (const char*)message1, strlen(message1), 
		0, (const struct sockaddr*)&servaddr, 
		sizeof(servaddr)); 

	for(;;){
		sleep(5);		
		sendto(sockfd_UDP, (const char*)message1, strlen(message1), 
		0, (const struct sockaddr*)&servaddr, 
		sizeof(servaddr)); 
	}
}

int main() 
{ 

	int rc;
	int i;
	
	
	pthread_t thread_array[NUM_THREADS];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	rc = pthread_create(&thread_array[0], NULL, TCP_CALL, (void*) NULL);
	rc = pthread_create(&thread_array[1], NULL, UDP_CALL, (void*) NULL);
	
	for(int i = 0;i<2;i++){
		pthread_join(thread_array[i],NULL);
	}

	
	
	 
} 
