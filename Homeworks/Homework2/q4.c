#include <sys/types.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <time.h>

int main()
{  
    struct timeval tv;
    int i; 
    int length = 256;
    int * arrptr1 = (int*)malloc(sizeof(int)*length);
    int * arrptr2 = (int*)malloc(sizeof(int)*length);
    time_t t;

    printf("Before sort-\n");
    srand((unsigned) time(&t));
    for(i = 0; i < length; i++)
    {
		arrptr1[i] =48 + rand()%96;
		printf("%d, ",arrptr1[i]);
    }
    printf("\n");	

    int status = 0;

    status = syscall(333,arrptr1,length,arrptr2);
         
    if(status == 0) 
    {
	printf("After sort\n");
	for(i = 0; i < length; i++)
	{
		printf("%d, ",arrptr2[i]);
	}
	printf("\n");
	printf("Sorting succssful\n");		
    }	
    else 
    {
         printf("System call failed:%ld \n",status);
    }

    printf("Current process ID: %ld \n", syscall(39));
    printf("Current user ID: %ld \n", syscall(102));
    int j = syscall(96, &tv, NULL);
    if(j == 0)
    {
	printf("Current date and time: %ld \n", tv.tv_sec);
    }
    else
    {
	printf("Syscall failed");
    }
    return (0);
}
