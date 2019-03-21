#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <sys/shm.h> 

int main(){

	char *message,*read;

	pid_t fr;
	key_t key;int shmid;char *str;
	
	fr=fork();
	
	if(fr==-1){
	
		fprintf(stderr,"Fork error");
		return 0;
	
	}	
	else if(fr>0){
	
		key_t kw;
		kw = ftok("mem",65);	
		int shmid = shmget(kw,1024,0666|IPC_CREAT); 
		message = (char*) shmat(shmid,(void*)0,0);
		printf("Message: ");
		gets(message);
		shmdt(message);
		
	}
	else{
	
		sleep(3);
		key_t kr;
		kr = ftok("mem",65);
		int shmid = shmget(kr,1024,0666|IPC_CREAT);
		read = (char*) shmat(shmid,(void*)0,0);
		printf("Shared Memory returned: %s",read);
		shmdt(read);
		shmctl(shmid,IPC_RMID,NULL);
		return 0;	
	}

}
