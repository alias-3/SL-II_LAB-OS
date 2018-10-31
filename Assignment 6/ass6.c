#include<stdio.h>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>


sem_t forks[5];
sem_t room;
int count[5]={0};

void *philo(void *arg)
{
	int j= *(int*)arg;
	while(count[j]<10)
	{
		printf("philsopher %d is thinking\n",j);
		sleep(2);
		sem_wait(&room);
		sem_wait(&forks[j]);
		sem_wait(&(forks[(j+1)%5]));
		printf("philsopher %d is eating for %d th time\n",j,(count[j]+1));
		count[j]+=1;
		sem_post(&forks[(j+1)%5]);
		sem_post(&forks[j]);
		sem_post(&room);
	}
	printf("philsopher %d exiting room\n",j);
	sleep(2);
	pthread_exit(NULL);

}

int main()
{
	int temp[5];
	int i;
	pthread_t phil[5];
	
	sem_init(&room,0,4);
	
	for(i=0;i<5;i++)
		sem_init(&forks[i],0,1);

	for(i=0;i<5;i++)
	{
		temp[i]=i;
		pthread_create(&phil[i],NULL,philo,&temp[i]);
	}

	for (int i = 0; i < 5;i++)
	{
		pthread_join(phil[i],NULL);
	}

	sem_destroy(&room);
	
	for(i=0;i<5;i++)
		sem_destroy(&forks[i]);

	return 0;

}