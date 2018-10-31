#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int arr1[3][3];
int arr2[3][3];
int res[3][3];

void *status = NULL;
void *result(void *arg);
void display(int a[3][3])
{
	int i,j;
	for(i=0;i<3;i++)
 	{
 		for(j=0;j<3;j++)
 		{
 			printf("%d\t",a[i][j]);
 		}
 		printf("\n");
 	}
}
int total;
int sum;
int res1;

struct v{
	int i,j;
};

void main(){
	pthread_t tid;
	int i,j;
 	struct v *data = (struct v *) malloc(sizeof(struct v));
 	
 	printf("\nenter first matrix\n");
 	for(i=0;i<3;i++)
 	{
 		for(j=0;j<3;j++)
 		{
 			scanf("%d",&arr1[i][j]);
 		}
 	}
 	display(arr1);

 	printf("\nenter second matrix\n");
 	for(i=0;i<3;i++)
 	{
 		for(j=0;j<3;j++)
 		{
 			scanf("%d",&arr2[i][j]);
 		}
 	}
 	display(arr2);
 	
 	for(i=0;i<3;i++)
 	{
 		for(j=0;j<3;j++)
 		{
 			data->i=i;
 			data->j=j;
 			pthread_create(&tid,NULL,result,data);
 			pthread_join(tid,&status);
 			res1 = *((int *)status);
 			res[i][j]=res1;
 		}
 	}

 	printf("The resultant matrix is : \n");
 	display(res);


}





void *result(void *arg){
	struct v *data1=arg;
	sum=0;
	int k;
	for(k=0;k<3;k++)
	{
		sum += arr1[data1->i][k] * arr2[k][data1->j];
	}
	pthread_exit(&sum);
}