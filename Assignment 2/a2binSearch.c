#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>


int bs(int key,int start,int end,int a[]){

	int m ;
	if(start<=end){
		m = (start + end)/2;
		if(key==a[m])
		{
			printf("found at pos : %d\n",m+1);
			return;
		}
		else if(key<a[m])
		{
			return bs(key,start,m-1,a);
		}
		else
			return bs(key,m+1,end,a);
	}
	
	printf("not found\n");
	return -1;
}


void arrtoint(char *argv[],int a[],int count)
{
	int i=1;
	for(i=1;i<=count;i++)
	{
		a[i-1] = atoi(argv[i]);
	}
}


main(int argc,char* argv[])
{
	printf("success\n");
	int count = atoi(argv[0]);
	int a[count];
	arrtoint(argv,a,count);
	int i;
	printf("recieved array is : \n");
	for(i=0;i<count;i++)
	{
		printf("%d\n",a[i]);
	}
	int start = 0;
	int end = count -1;
	int key;
	printf("enter key to search\n");
	scanf("%d",&key);
	bs(key,start,end,a);

}