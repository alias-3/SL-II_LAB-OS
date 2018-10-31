#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

void main(){
	key_t key = 0122;
	char * shm,*s;
	int size =20;
	int shid  = shmget(key,size,IPC_CREAT | 0666);
	if(shid < 0)
	{
		printf("eror creating sh memory\n");
		return;
	}
	shm = shmat(shid,NULL,0);
	if(shm==(char *)-1)
	{
		printf("error connecting to s memo\n");
		return;
	}
	s= shm;
	printf("succrssfully create shard space\n");
	printf("enter message\n");
	gets(s);

	while(s!="*")
		sleep(1);

}