#include <stdio.h>
#include <fcntl.h>	
#include <unistd.h>
#include <string.h>

void main(){
	int words=0,lines=0,chars=0,i=0;

	int fd = open("myfifo",O_RDONLY);
	char arr[800];
	read(fd,arr,sizeof(arr));
	printf("recvd data: %s\n",arr);
	while(arr[i]!='\0')
	{
		if(arr[i]== ' ' || arr[i]== '\n')
		{
			++words;
		}
		if(arr[i]=='\n')
		{
			++lines;
		}
		if(!(arr[i]=='\n'))
		{
			++chars;
		}
		i++;
	}	
	printf("words: %d\n",words);
		printf("lines:%d \n",lines);
		printf("charss:%d \n",chars);
		close(fd);
}
