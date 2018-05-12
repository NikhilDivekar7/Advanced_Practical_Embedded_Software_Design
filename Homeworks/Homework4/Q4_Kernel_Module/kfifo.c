#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/kfifo.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nikhil Divekar");
MODULE_DESCRIPTION("Kfifo kernel module");

struct task_struct * thread1;
struct task_struct * thread2;

int KFIFO_SIZE = 16
static int Time = 5;

static DECLARE_KFIFO(example, struct task_struct*, KFIFO_SIZE);

int thread1_func(void * data)
{
	
	printk(KERN_INFO "Starting thread 1");			//thread 1 function

        while(!kthread_should_stop())
        {      
                if(kfifo_put(&example, current)==0)
                {
                	printk("Ful buffer\n");
                }
                ssleep(Time);					//wait for time interval
        }

        return 0;
}

int thread2_func(void * data)
{
	printk(KERN_INFO "Starting thread 1");
	struct task_struct * mydata;	
	struct task_struct * current_task;
	if(kfifo_get(&example, &mydata == 0))
        {
               printk("Empty FIFO\n");
        }
	else
	{
		current_task = current;			//printing details
		printk(KERN_INFO "Current Pid : %d, vruntime: %llu", current->pid, current->se.vruntime);
		printk(KERN_INFO "Previous Pid : %d, vruntime: %llu", list_prev_entry(mydata, tasks)->pid, list_prev_entry(mydata, tasks)->se.vruntime);
		printk(KERN_INFO "Next Pid : %d, vruntime: %llu", list_next_entry(mydata, tasks)->pid, list_next_entry(mydata, tasks)->se.vruntime);
	}
	printk(KERN_INFO "Thread 2 functionality done");
	return 0;
}

static int __init my_init(void)
{
	printk(KERN_INFO "Starting kfifo kernel module");
	INIT_KFIFO(example);
	
	thread1 = kthread_create(thread1_func, NULL, "first thread");		//creating threads
	if(IS_ERR(thread1))
	{
		printk(KERN_ERR "Thread 1 not created");
	}
	else
	{
		printk(KERN_INFO "Thread 1 created");
	}

	thread2 = kthread_create(thread2_func, NULL, "Second thread");
	if(IS_ERR(thread2))
	{
		printk(KERN_ERR "Thread 2 not created");
	}
	else
	{
		printk(KERN_INFO "Thread 2 created");
	}
	
	return 0;
}

static void __exit my_exit(void)
{
	kthread_stop(thread1);	
	printk(KERN_INFO "Thread 1 stopped");			//deleting threads

	kthread_stop(thread2);
	printk(KERN_INFO "Thread 2 stopped");
}

module_init(my_init);
module_exit(my_exit);
