#include <linux/module.h>
#include <linux/kernel.h> 
#include <linux/init.h>
#include <linux/timer.h>
 
int timegap = 500;
struct timer_list myTimer;
char *my_name;
int counts;

module_param(my_name, charp , S_IRUSR | S_IWUSR);
module_param(counts, int , S_IRUSR | S_IWUSR);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nikhil");
MODULE_DESCRIPTION("THIS IS MY TIMER");
 
void _timerHandler(unsigned long data)
{
    mod_timer( &myTimer, jiffies + msecs_to_jiffies(timegap));
    counts++;
    printk(KERN_INFO "Timer Handler called.\n");
    printk(KERN_INFO "Name: %s Count: %d\n", my_name,counts);
}
 
static int __init my_init(void)
{
    printk(KERN_INFO "Module inserted \n");
    setup_timer(&myTimer_timerHandler, 0);
    mod_timer( &myTimer, jiffies + msecs_to_jiffies(timegap));
 
    return 0;
}
 
static void __exit my_exit(void)
{
    del_timer(&myTimer);
    printk(KERN_INFO "Module removed\n");
}
 
module_init(my_init);
module_exit(my_exit);
