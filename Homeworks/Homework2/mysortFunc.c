Syscall:
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE3(mysortFunc, const int __user *, arrptr1, int , length , int __user  * , arrptr2)
{
    printk("Entering system call\n");
    int i,j,temp = 0;
    int *kernelBuff = NULL;
    int kernelBuffLength;
    kernelBuffLength = (sizeof(int)*length);

    kernelBuff = (int*)kmalloc( kernelBuffLength, GFP_KERNEL);
    
    if(kernelBuff == NULL)
    {
          printk(KERN_ERR "Kernel buffer not created properly\n");
          kfree(kernelBuffer);
          return -ENOMEM;
    }

    if (arrptr1 == NULL || arrptr2 == NULL)
    {
          printk(KERN_ERR "Null Pointer passed \n");
          return -EFAULT;
    }

    if( length < 256 )
    {
       printk(KERN_ERR "Buffer must have at least 256 elements\n");
       return -EINVAL;
    }

    if( length < 0 )
    {
       printk(KERN_ERR "Invalid length\n");
       return -EINVAL;
    }

    if(copy_from_user(kernelBuff, arrptr1, kernelBuffLength))
    {
          printk(KERN_ERR "Not all data was copied from user\n");
          return -EFAULT;
    }

    printk(KERN_INFO "No errors. Proceeding with sort");
    
    for(i=0;i<(length-1);i++)
    {
        for(j=0;j<(length-i-1);j++)
        {
            if(*(kernelBuff + j) < *(kernelBuff + j + 1))
            {
             temp = *(kernelBuff + j);
             *(kernelBuff + j) = *(kernelBuff + j + 1);
             *(kernelBuff +j +1) = temp;
            }
        }
    }

    if(copy_to_user(arrptr2, kernelBuff, kernelBuffLength))
    {
       printk(KERN_ERR "Not all data was copied to user\n");
       return -EFAULT;
    }
    
    printk(KERN_INFO "Done with system call \n");

    return 0;
}
