#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>


pthread_mutex_t writer1;
pthread_mutex_t reader1;
FILE * fp;
char filename[20];
char c;
int readcount =0;

void *writer(void *arg){
	pthread_mutex_lock(&writer1);
	printf("enter file name to write contents\n");
	scanf("%s",filename);
	fp =fopen(filename,"a");
	while(c!='`')
	{
		fputc(c,fp);
		scanf("%c",&c);
	}
	fclose(fp);
	sleep(1);
	pthread_mutex_unlock(&writer1);
	pthread_exit(NULL);

}

void *reader(void *arg){
	pthread_mutex_lock(&reader1);
	readcount++;
	if(readcount==1)
		pthread_mutex_lock(&writer1);
	pthread_mutex_unlock(&reader1);

	printf("enter file name to read\n");
	scanf("%s",filename);
	fp = fopen(filename,"r");
	while(!feof(fp))
	{
		c= fgetc(fp);
		printf("%c",c );
	}
	fclose(fp);
	sleep(1);
	pthread_mutex_lock(&reader1);
	readcount--;
	if(readcount==0)
		pthread_mutex_unlock(&writer1);
	pthread_mutex_unlock(&reader1);
	pthread_exit(NULL);
}

void main(){
	pthread_mutex_init(&writer1,NULL);
	pthread_mutex_init(&reader1,NULL);
	pthread_t thread[10];
	int i;
	for(i=0;i<10;i++)
	{
		pthread_create(&thread[i],NULL,writer,NULL);
		i++;
		pthread_create(&thread[i],NULL,reader,NULL);
	}

	for(i=0;i<10;i++)
	{
		pthread_join(thread[i],NULL);
	}

	pthread_mutex_destroy(&writer1);
	pthread_mutex_destroy(&reader1);

}