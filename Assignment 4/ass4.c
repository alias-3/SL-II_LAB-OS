#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>

#define size 5
#define num_threads 10

int buffer[size];
sem_t full;
sem_t empty;
pthread_mutex_t buffer_mutex;
int bindex;

void insert(int a)
{
	if(bindex<size)
	{
		buffer[bindex++]=a;
	}
	else
		printf("overflow\n");
} 

int rem()
{
	if(bindex>0)
	{
		return (buffer[--bindex]);
	}
	else
	{
		printf("underflow\n");
		return -1;
	}
}


void *prod(void *arg){
	int p = *(int*)arg;
	int value = rand()%100;
	sem_wait(&empty);
	pthread_mutex_lock(&buffer_mutex);
	insert(value);
	pthread_mutex_unlock(&buffer_mutex); 
	sem_post(&full);
	printf("prod %d inserted %d in buffer\n",p,value);
	pthread_exit(NULL);
}



void *cons(void *arg){
	int p = *(int*)arg;
	int value;
	sem_wait(&full);
	pthread_mutex_lock(&buffer_mutex);
	value = rem();
	pthread_mutex_unlock(&buffer_mutex); 
	sem_post(&empty);
	printf("cond %d removed %d from buffer\n",p,value);
	pthread_exit(NULL);
}



void main()
{
	int i,threadno[10];
	pthread_t thread[10];
	sem_init(&full,0,0);
	bindex =0 ;
	sem_init(&empty,0,size);
	pthread_mutex_init(&buffer_mutex,NULL);

	for (int i = 0; i < 10; i++)
	{
		threadno[i]=i;
		pthread_create(&thread[i],NULL,prod,&threadno[i]);
		sleep(1);
		i++;
		threadno[i]=i;
		pthread_create(&thread[i],NULL,cons,&threadno[i]);
	}

	for (int i = 0; i < 10;i++)
	{
		pthread_join(thread[i],NULL);
	}


	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&buffer_mutex);
}