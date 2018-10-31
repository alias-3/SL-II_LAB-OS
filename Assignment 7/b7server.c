#include <stdio.h>
#include <fcntl.h>	
#include <unistd.h>

void main(){

	char *myfifo = "myfifo";
	char s,s2[800];
	int c=0;
	mkfifo(myfifo,0777);
	
	printf("enter message end with $");
	int fd = open(myfifo,O_WRONLY);
	while((s=getchar())!='$')
	{
		s2[c++]=s;
	} 
	s2[c]='\0';
	write(fd,s2,c+2);
	close(fd);
	printf("server entered %s\n",s2);
}