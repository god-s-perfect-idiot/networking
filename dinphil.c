#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

#define LEFT (pn+4)% 5
#define RIGHT (pn+1)%5

sem_t mutex[5];
int state[5];
int pnum[5]={0,1,2,3,4};

void* thread(void* arg) 
{ 
	int k=(int)arg;
	printf("\n%d is thinking\n",k+1);
	sleep(2);
	printf("\n%d is hungry\n",k+1);
    sem_wait(&mutex[k]);
    sem_wait(&mutex[(k+1)%5]); 
    printf("\n%d Entered and is Eating hungrily\n",k+1);  
    sleep(4);  
    printf("\n%d is Just Exiting...\n",k+1); 
    sem_post(&mutex[k]);
    sem_post(&mutex[(k+1)%5]); 
} 

void main(){
	for(int i=0;i<5;i++){
		sem_init(&mutex[i],0,1);
	
	}
	pthread_t p1[5];
	while(1){
		for(int i=0;i<5;i++){
			pthread_create(&p1[i],NULL,thread,(void*)i);
			sleep(2);
		}
	}
    sem_destroy(&mutex[5]); 
}
