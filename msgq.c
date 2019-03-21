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
    		char mesg_text[100]; 
	
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
		
		kw = ftok("progfile", 65);
		msgid = msgget(kw, 0666 | IPC_CREAT); 
 		message.mesg_type = 1;
 		printf("Message: "); 
    		fgets(message.mesg_text,100,stdin);
    		msgsnd(msgid, &message, sizeof(message), 0);  
		
	}
	else{
	
		key_t kr;
		int msgid;	
		
		sleep(1);
		kr = ftok("progfile", 65);
		msgid = msgget(kr, 0666 | IPC_CREAT);
		msgrcv(msgid, &message, sizeof(message), 1, 0);  
		printf("Message queue retruned: %s",message.mesg_text); 
		msgctl(msgid, IPC_RMID, NULL); 
		return 0; 
	
	}
	
	
}
