#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>



void accept(int a[],int n){
	printf("enter the elements\n");
	int i;
	for (i = 0; i < n; i++)
	{
		scanf("%d",&a[i]);
	}
}

void display(int a[],int n){
	printf("sorted elements\n");
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d\t",a[i]);
	}
}

void display2(int a[],int n){
	printf("sorted elements\n");
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d\t",a[i]);
	}
}
void swap(int *a, int *b){
	int p  = *a;
	*a = *b;
	*b = p;
}

void bubble(int a[],int n)
{
	int i,k;
	for(i=0;i<n-1;i++)
	{
		for(k=0;k<n-i-1;k++)
		{
			if(a[k]>a[k+1]) swap(&a[k],&a[k+1]);
		}
	}
}


int partition(int a[],int start,int end)
{
	int p = start-1;
	int i,pivot=a[end];
	for(i=start;i<end;i++)
	{
		if(a[i]<=pivot)
		{
			p++;
			swap(&a[p],&a[i]);
		}
	}
	swap(&a[p+1],&a[end]);
	return (p+1);
}


void qsort(int a[],int start,int end)
{
	if(start<end)
	{
		int p = partition(a,start,end);
		qsort(a,start,p-1);
		qsort(a,p+1,end);
	}
}


void main(){
	pid_t cpid;
	int n;
	printf("enter no of elements to sort\n");
	scanf("%d",&n);
	int a[n];
	accept(a,n);
	cpid = fork();
	switch(cpid){
		case -1: printf("error in proc creation\n");
				break;
		case 0 : printf("i am child\n");
				 qsort(a,0,n-1);
				 display(a,n);
				break;
		default : 	wait();
					printf("i am parent\n");
					bubble(a,n);
					display2(a,n);
					break;
	}
}
