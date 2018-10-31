#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

void swap(int *a,int *b){
	int p = *a;
	*a = *b ;
	*b = p;
}


int partition(int a[],int start,int end)
{
	int pivot=a[end];
	int i,p=start-1;
	for(i=start;i<end;i++)
	{
		if(a[i]<=pivot)
		{
			p++;
			swap(&a[i],&a[p]);
		}
	}
	swap(&a[p+1],&a[end]);
	return (p+1);

}

void quick(int a[],int start,int end){
	if(start<end){
		int p = partition(a,start,end);

		quick(a,start,p-1);
		quick(a,p+1,end);
	}
}


void main(){

	char *str[30];

	printf("enter num of elements: \n");
	int n;
	scanf("%d",&n);

	printf("enter the elements\n");
	int a[n],i=0;
	for(i=0;i<n;i++)
	{
		scanf("%d",&a[i]);
	}

	printf("the elements\n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}
	
	quick(a,0,n-1);
	printf("sorted array is : \n");
	for(i=0;i<n;i++)
	{
		printf("%d\t",a[i]);
	}

	int *status = NULL;
	pid_t cpid;
	cpid = fork();
	switch(cpid)
	{
		case -1: printf("error in pro creation\n");
				 break;
		case 0: 
				printf("\nchild created\n");
				asprintf(&str[0],"%d",n);
				puts(str[0]);
				for (i = 0; i < n; i++)
				{
					asprintf(&str[i+1],"%d",a[i]);
				}
				execve("bins.out",str,NULL);
				break;
		default: 
				wait(status);
				printf("parent is : %d\n",(int)getppid());
	}

}



