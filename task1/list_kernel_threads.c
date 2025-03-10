#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/uaccess.h>

static int __init list_kernel_threads_init(void) {
    struct task_struct *task;
    printk(KERN_INFO "Listing all kernel threads:\n");

    // 遍历所有进程
    for_each_process(task) {
        // 过滤只显示内核线程，排除用户空间进程
        if (task->flags & PF_KTHREAD) {
            // 打印内核线程的相关信息
            printk(KERN_INFO "Name: %s, PID: %d, State: %ld, Priority: %d, Parent PID: %d\n",
                task->comm, task->pid, task->state, task->prio, task->real_parent->pid);
        }
    }

    return 0;
}

static void __exit list_kernel_threads_exit(void) {
    printk(KERN_INFO "Kernel thread listing module unloaded.\n");
}

module_init(list_kernel_threads_init);
module_exit(list_kernel_threads_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module to list all kernel threads");
