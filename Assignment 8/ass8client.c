#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>

void main(){
	key_t key = 0122;
	char * shm,*s;
	int size =20;
	int shid = shmget(key,size,0666);
	if(shid<0)
	{
		printf("error in creation\n");
		return;
	}
	shm = shmat(shid,NULL,0);
	if(shm==(char * )-1)
	{
		printf("error in connection\n");
		return;
	}
	s =shm;
	puts(s);
	s = "*";
}

