// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 

/**
	This is a client for sending TCP messages to a server.
*/

/**
	This function checks if input1 matches the exitChar string.
	Return: 0 if message matches exitChar
*/
int exitFunc(char* input1, char* input2){
	int c = -4;
		for(int i = 0;i<4;i++){
			if(input1[i] == input2[i]){
			c++;
		}
	}
	return c;
}

int main(int argc, char const *argv[]) { 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 

	int exit = 0;

	char exitChar[1024] = "exit"; // Used to check input message
	char message[1024]; // Used for message to send to server
	char buffer[2048] = {0}; // Used for response message from server


	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	memset(&serv_addr, '0', sizeof(serv_addr)); 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	}
	while(exit == 0){ 

		printf("Type 'exit' to exit");
		printf("\n");

		if(fgets(message,100,stdin)){
			if(exitFunc(message,exitChar) == 0){ //Client closes after exit string is inputted
				printf("Exiting... \n");
				return 0;
			}
			send(sock , message , strlen(message) , 0 );
			printf("You: %s\n", message);
		}
		if(read( sock , buffer, 2048)) printf("Server: %s\n",buffer );
	}
	return 0; 
}
