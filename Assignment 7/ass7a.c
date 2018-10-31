#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

void main(){
	int fd[2],pd[2],i=0;
	char  msg[] = "anurag.txt";
	char  msg2[100];
	char ch;
	pipe(fd);
	pipe(pd);
	pid_t cpid;
	FILE *fp;
	cpid = fork();
	switch(cpid)
	{
		case 0: printf("reading file path from parent\n");
				read(fd[0],msg,sizeof(msg));
				close(fd[0]);
				fp = fopen(msg,"r");
				while((ch=fgetc(fp))!=EOF)
				{
					msg2[i]=ch;
					i++;
				}
				fclose(fp);
				printf("sending file contents\n");
				write(pd[1],msg2,sizeof(msg2));
				close(pd[1]);
				break;

		default: 
				printf("writing file path to child\n");
				write(fd[1],msg,sizeof(msg));
				close(fd[1]);
				wait();
				printf("reading file contents got from child\n");
				read(pd[0],msg2,sizeof(msg2));
				close(pd[0]);
				printf("The cotents are: \n %s",msg2);
				wait();
		
	}
}