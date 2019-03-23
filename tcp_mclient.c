// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 4400 

int main(int argc, char const *argv[]) 
{ 
	struct sockaddr_in address; 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	int buffer[3][3];
	int number[3][3];
	
	for(int i=0;i<3;i++){
	
		for(int j=0;j<3;j++){
		
			number[i][j]=i;
		
		}
	} 
	 
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
	send(sock , &number , sizeof(number) , 0 ); 
	printf("Request Matrix sent\n"); 
	valread = read( sock , &buffer, sizeof(buffer)); 
	
	for(int i=0;i<3;i++){
	
		for(int j=0;j<3;j++){
		
		printf("%d\t",buffer[i][j] ); 
		
		}
		printf("\n");
	}
	 
	return 0; 
} 

