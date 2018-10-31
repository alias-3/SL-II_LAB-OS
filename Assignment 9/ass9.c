#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>


typedef struct emp{
	int id;
	char name[20];
}emp;



int check(int a){
	emp e;
	int fc = open("test",O_RDONLY);
	while(read(fc,&e,sizeof(e))>0)
	{
		if(e.id==a)
		{
			close(fc);
			return 1;
		}
	}
	close(fc);
	return 0;
}

void insert(){
	emp e;
	printf("enter id: \n");
	scanf("%d",&e.id);
	if(check(e.id))
	{
		printf("record already exists");
		return;
	}
	printf("enter name: \n");
	scanf("%s",e.name);
	int fd= open("test", O_WRONLY | O_APPEND);
	write(fd,(void *)&e,sizeof(e));
	close(fd);
}

void display(){
	emp e;
	printf("displaying records\n");
	int fd = open("test", O_RDONLY);
	while(read(fd,&e,sizeof(e)))
	{
		printf("id: %d\n",e.id);
		printf("name: %s\n",e.name);
	}
	close(fd);
}


void delete(){
	emp e;
	int p;
	
	printf("enter id to delete\n");
	scanf("%d",&p);
	if(!check(p))
	{
		printf("record not found\n");
		return;
	}
	else{
		
		printf("asdsdasd\n");
		int fp = open("temp",O_WRONLY);
		int fd =open("test",O_RDONLY);
		if(fd!=-1&& fd!=-1)
		{
			while(read(fd,&e,sizeof(e)))
			{
				if(e.id==p)
				{
					printf("deleting now");
				}
				else
					write(fp,(void *)&e,sizeof(e));
			}
		}
		close(fd);
		close(fp);
		remove("test");
		rename("temp","test");	
	}
}


void search(){
	int fd = open("test",O_RDONLY);
	emp e;
	int no;
	printf("enter id to search\n");
	scanf("%d",&no);
	while(read(fd,&e,sizeof(e))>0){
		if(e.id==no)
		{
			printf("name : %s\n",e.name);
			printf("id : %d\n",e.id );
			close(fd);
			return;
		}
	}
	close(fd);
	printf("not found\n");

}

void update(){
	emp e;
	int old,new,flag=9;
	int fd = open("test",O_RDWR);

	if(fd!=-1)
	{
		printf("enter record number to modify\n");
		scanf("%d",&old);
		while(read(fd,&e,sizeof(e)))
		{
			if(e.id==old)
			{
				printf("enter new id: \n");
				scanf("%d",&new);
				if(check(new))
				{
					printf("exists\n");
					return;
					
				}

				lseek(fd,0-sizeof(e),SEEK_CUR);
				e.id = new;
				printf("enter name: \n");
				scanf("%s",e.name);
				write(fd,(void *)&e,sizeof(e));
				break;
			}
		}
		
	}
	if(flag==0)
			printf("not modified\n");
		close(fd);
}

void main(){
	int ch;
	int fd = open("test",O_CREAT | O_APPEND, 0777);
	int fp = open("temp",O_CREAT | O_APPEND, 0777);
	if(fd!=-1)
		printf("file successfully created\n");
	close(fd);
	close(fp);
	do{
		printf("Enter your choice\n");
		printf("1: insert\n");
		printf("2: view\n");
		printf("3: delete\n");
		printf("4: update\n");
		printf("5: search\n");
		printf("6: exit\n");
		scanf("%d",&ch);
		switch(ch){
			case 1: insert();
					break;
			case 2: display();
					break;
			case 3: delete();	
					break;
			case 4: update();
					break;
			case 5: search();
					break;
			case 6: break;
			default: printf("wrong choice\n");
		}		
	}while(ch<=6);
}

