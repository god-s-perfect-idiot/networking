#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 


int main(){
	
	int pipe_end[2];
	
	pid_t fr;
	
	char input_str[100];
	char output_str[100];
	
	if (pipe(pipe_end)==-1){
	
		fprintf(stderr,"Pipe failed!");
		return 1;
	
	}

	printf("Message: ");
	fgets(input_str,100,stdin);
	fr=fork();
	
	if(fr<0){
	
		fprintf(stderr,"Fork failed!");
		return 1;
	
	}	
	else if(fr>0){
	
		close(pipe_end[0]);
		write(pipe_end[1],input_str,strlen(input_str)+1);
		close(pipe_end[1]);
		
	}
	else{
		sleep(3);
		close(pipe_end[1]);
		read(pipe_end[0],output_str,100);
		close(pipe_end[0]);
		printf("Pipe returned: %s",output_str);
		return(0);
	
	}
	
	
}
