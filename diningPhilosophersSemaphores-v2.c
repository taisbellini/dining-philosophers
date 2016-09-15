#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "diningPhilosophersSemaphores.h"

int num = 0;
int *states;
sem_t *forks;

char getStateName(int state){
	switch(state){
		case EATING: return 'E'; break;
		case THINKING: return 'T'; break;
		case HUNGRY: return 'H'; break;
	}
}

void* philosopher (void* arg)
{
	
	int n =*((int *)arg);
	int left = n;
	int right = (n + 1) % num;
	while(1)
	{ 		
			
		/*get the forks */ 
		sleep(rand()%10+1);
		/*if its the first (there is at least one philosopher) gets first with left hand, else, gets with right. 
		Breaks the cicle to avoid deadlock. */		
		states[n] = HUNGRY;		
		if (n==0)
		{
			sem_wait(&forks[left]);
			sem_wait(&forks[right]);
			states[n] = EATING;
		}else
		{
			sem_wait(&forks[right]);
			sem_wait(&forks[left]);
			states[n] = EATING;
		}

		sleep(rand()%10+1);

		/*drop the forks */
		sem_post(&forks[left]);
		sem_post(&forks[right]);
		states[n] = THINKING;
		
	}	
}


int main(int argc, char *argv[ ]) {
    
	if (argc > 1)
	{		
		num = atoi(argv[1]);
		if (num < 1)
		{
			printf("We need at least one philosopher\n");
			return -1;
		}
	}
	else
	{
		printf("Define a number of philosophers!\n");
		return -1;
	}

	int i;
	states = malloc(sizeof(int)*num);	
	
	for (i=0; i<num; i++)
	{
		states[i] = THINKING;
	}
	
	forks = malloc(sizeof(sem_t)*num);
	
	pthread_t philosophers[num];
	
	for(i=0; i<num;i++)
	{  		
		//initialize semaphores for the forks all in 1
    		sem_init(&forks[i], 0, 1);
			int *arg= malloc (sizeof(int));
			*arg = i;		
    		//creates a ther for each philosopher
    		pthread_create(&philosophers[i], NULL, philosopher, (void *)arg);
	}

	// print the states
	char state;
	int j;
	while(1)
	{
		sleep(1);

    		for (j=0; j<num; j++)
		{
			state = getStateName(states[j]);
			printf(" %c - ", state);
		}
		printf("\n");
		
	}
    

	pthread_exit(0); 
}

