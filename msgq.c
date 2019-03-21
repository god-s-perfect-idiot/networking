#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 



int main(){
	
	struct mesg_buffer { 
    	
    		long mesg_type; 
    		int arr[3][3]; 
	
	} message; 
	
	pid_t fr;	

	fr=fork();
	
	if(fr<0){
	
		fprintf(stderr,"Fork failed!");
		return 1;
	
	}	
	else if(fr>0){
	
		key_t kw;
		int msgid;
		
		kw = ftok("msgq", 65);
		msgid = msgget(kw, 0666 | IPC_CREAT); 
 		message.mesg_type = 1;
 		for(int i=0;i<3;i++){
 			for(int j=0;j<3;j++){
 				printf("Array[%d][%d]: ",i+1,j+1); 
    				scanf("%d",&message.arr[i][j]);
    			}
    		}
    		msgsnd(msgid, &message, sizeof(message), 0);  
		
	}
	else{
	
		key_t kr;
		int msgid;	
		
		sleep(3);
		kr = ftok("msgq", 65);
		msgid = msgget(kr, 0666 | IPC_CREAT);
		msgrcv(msgid, &message, sizeof(message), 1, 0);  
		printf("Diagonal elements from Queue: ");
		for(int i=0;i<3;i++){
 			for(int j=0;j<3;j++){
 				if(i==j){
 					printf("%d ",message.arr[i][j]);
    				}
    			}
    		}
		msgctl(msgid, IPC_RMID, NULL); 
		return 0; 
	
	}
	
	
}
