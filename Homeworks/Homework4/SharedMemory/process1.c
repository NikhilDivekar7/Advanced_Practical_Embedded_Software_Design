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
#include <sys/types.h>
#include <stdlib.h>

#define shared_memory_name	"my_sm"
#define semaphore_name 		"my_semaphore"

typedef struct{
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
	printf("Currently in process 1\n");
	
	int sm_fd = shm_open(shared_memory_name, O_CREAT | O_RDWR, 0666);	//create shared memory
	if(sm_fd < 0)
	{
		perror("Cannot access shared memory");
		exit(1);
	}

	int sm_size = sizeof(data);

	int value = ftruncate(sm_fd, sm_size);
	if(value < 0)
	{
		perror("Ftruncate error");
		exit(1);
	}

	data * shared_mem = mmap(NULL, sm_size, PROT_READ | PROT_WRITE, MAP_SHARED , sm_fd, 0);	//memory mapping
	if(shared_mem < 0)
	{
		perror("Mapping error");
		exit(1);
	}

	sem_t * sem = sem_open(semaphore_name, O_CREAT, 0666, 0);			//open semaphore
	if(sem == NULL)
	{
		perror("Semaphore error");
		exit(1);	
	}

	char msg[] = "Hello from Process1";
    	data Sent_data;

    	strcpy(Sent_data.my_string,msg);
    	Sent_data.my_string_length = strlen(Sent_data.my_string);
    	Sent_data.LED_Control = LED_OFF;

    	memcpy(shared_mem, &Sent_data, sm_size);

    	sem_post(sem);

    	data Received_data;

    	memcpy(&Received_data, shared_mem, sm_size);

	printf("Message from process 2\n");
    	printf("Message: %s\nMessageLen: %d\nUSRLED: %d\n",Received_data.my_string,Received_data.my_string_length,Received_data.LED_Control);

	value = shm_unlink(shared_memory_name);			//unlink shared memory
	if(value < 0)
	{
		perror("Unlink error");
		exit(1);
	}

	return 0;
}
