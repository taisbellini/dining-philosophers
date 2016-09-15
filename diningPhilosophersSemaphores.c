#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "diningPhilosophersSemaphores.h"

int num = 0;
int *states;
sem_t *forks;
sem_t mutex;

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
			
		/* GET THE FORKS */ 
		sleep(rand()%10+1);
		// get both forks atomically to avoid deadlock		
		states[n] = HUNGRY;
		sem_wait(&mutex);		

		sem_wait(&forks[left]);
		sem_wait(&forks[right]);
		states[n] = EATING;

		sem_post(&mutex);

		sleep(rand()%10+1);

		/* DROP THE FORKS */
		sem_post(&forks[left]);
		sem_post(&forks[right]);
		states[n] = THINKING;
		
	}	
}


int main(int argc, char *argv[ ]) {
    
	if (argc > 1)
	{
		num = atoi(argv[1]);
	}
	else
	{
		printf("Define the number of philosophers!");
		return -1;
	}

	int i;
	states = malloc(sizeof(int)*num);	
	
	for (i=0; i<num; i++)
	{
		states[i] = THINKING;
	}
	
	forks = malloc(sizeof(sem_t)*num);
	
	sem_init(&mutex, 0, 1);
	pthread_t philosophers[num];
	
	for(i=0; i<num;i++)
	{  		
		//initialize semaphores for forks all in 1
    		sem_init(&forks[i], 0, 1);
			int *arg= malloc (sizeof(int));
			*arg = i;		
    		//create thread for each philosopher
    		pthread_create(&philosophers[i], NULL, philosopher, (void *)arg);
	}

	// print of states
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

