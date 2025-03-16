#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int __init list_kernel_threads_init(void)
{
    struct task_struct *task;
    printk(KERN_ALERT "名称\t进程号\t状态\n");

    for_each_process(task) {
        printk(KERN_ALERT "%s\t%d\t%ld\n",
               task->comm, task->pid, task->stats);
    }

    return 0;
}

static void __exit list_kernel_threads_exit(void)
{
    printk(KERN_INFO "Kernel thread listing module unloaded.\n");
}

module_init(list_kernel_threads_init);
module_exit(list_kernel_threads_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module to list all kernel threads");
