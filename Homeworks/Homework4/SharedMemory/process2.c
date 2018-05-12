#include <sys/mman.h>
#include <sys/stat.h>   
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <stdlib.h>

#define shared_memory_name 	"my_sm"
#define semaphore_name 		"my_semaphore"

typedef struct
{
	char my_string[20];	
	int my_string_length;
	int LED_Control;
}data;

typedef enum
{
	LED_ON,
	LED_OFF
}LED_Enum;


int main()
{
	printf("Starting the process 2\n");	
	int sm_fd = shm_open(shared_memory_name, O_CREAT | O_RDWR, 0666);		//open shared memory
	if(sm_fd < 0 )
	{
		perror("Cannot access shared memory");
		exit(1);
	}

	int sm_size = sizeof(data);

	void *shared_mem = mmap(NULL, sm_size, PROT_READ | PROT_WRITE, MAP_SHARED , sm_fd, 0);	//memory mapping
	if(shared_mem == (void *)-1)
	{
		perror("Mapping error");
		exit(1);
	}

	sem_t * sem = sem_open(semaphore_name, O_CREAT, 0666, 0);		//openm semaphore
	if(sem == NULL)
	{
		perror("Semaphore error");
		exit(1);	
	}

	sem_wait(sem);

	data Received_data = {0};
        char *my_ptr = (char*)&Received_data;

        memcpy(my_ptr,(char*)shared_mem, sm_size);				//copy to shared memory

	printf("Message from Process 1 \n");
        printf("Message: %s\nMessage Length: %d\nLED: %d\n",Received_data.my_string,Received_data.my_string_length,Received_data.LED_Control);

        char msg[] = "Hello from Process2";
        data Sent_data ;
        my_ptr = (char*)&Sent_data;

        strcpy(Sent_data.my_string,msg);
        Sent_data.my_string_length = strlen(Sent_data.my_string);
        Sent_data.LED_Control = LED_ON;

        memcpy((char*)shared_mem, my_ptr, sm_size);				//copy from memory

    	sem_post(sem);

	close(sm_fd);
  	sem_unlink(semaphore_name);	
	return 0;
}
