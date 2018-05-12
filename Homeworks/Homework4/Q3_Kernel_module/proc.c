#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nikhil Divekar");
MODULE_DESCRIPTION("This is process tree example");

extern struct task_struct init_task;
int count;

static int __init my_init(void)
{
	printk(KERN_INFO "Starting my process tree example");
	printk(KERN_INFO "Executing process tree details");
	struct list_head *node;
	int count = 0;
	struct task_struct * task = current;
	while(task->pid != 0)
	{
		printk(KERN_INFO "Thread Name: %s \n", task -> comm);		//printing details
		printk(KERN_INFO "Process status: %d \n", task -> state);
		printk(KERN_INFO "Process ID: %d \n", task -> pid);

		list_for_each(node, &task -> children)
		{
			count++;
		}
		printk(KERN_INFO "Number of children: %d \n", count);
		count = 0;
		printk(KERN_INFO "Nice Values: %d \n", task_nice(task));
		task = task -> parent;
	}
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Exiting process tree example");
}

module_init(my_init);
module_exit(my_exit);
