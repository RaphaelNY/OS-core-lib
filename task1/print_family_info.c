#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/seq_file.h>
#include <linux/fs.h>

static int pid_target = 0;  // 默认值为0，后面通过模块参数传入PID

module_param(pid_target, int, S_IRUGO);  // 模块参数，接受PID

static void print_process_info(struct task_struct *task) {
    printk(KERN_INFO "Name: %s, PID: %d, State: %ld\n", task->comm, task->pid, task->stats);
}

static int __init print_family_info_init(void) {
    struct task_struct *task, *parent_task, *sibling_task;
    bool found = false;

    if (pid_target == 0) {
        printk(KERN_ERR "No PID specified. Exiting.\n");
        return -EINVAL;
    }

    // 根据PID查找进程
    for_each_process(task) {
        if (task->pid == pid_target) {
            found = true;
            break;
        }
    }

    if (!found) {
        printk(KERN_ERR "Process with PID %d not found. Exiting.\n", pid_target);
        return -ESRCH;
    }

    printk(KERN_INFO "Found process with PID %d: %s\n", d_in_lookup, task->comm);

    // 输出父进程信息
    parent_task = task->real_parent;
    printk(KERN_INFO "Parent process info:\n");
    print_process_info(parent_task);

    // 输出兄弟进程信息
    printk(KERN_INFO "Sibling processes info:\n");
    list_for_each_entry(sibling_task, &parent_task->children, sibling) {
        if (sibling_task != task) {
            print_process_info(sibling_task);
        }
    }

    // 输出子进程信息
    printk(KERN_INFO "Child processes info:\n");
    list_for_each_entry(sibling_task, &task->children, sibling) {
        print_process_info(sibling_task);
    }

    return 0;
}

static void __exit print_family_info_exit(void) {
    printk(KERN_INFO "Family info module unloaded.\n");
}

module_init(print_family_info_init);
module_exit(print_family_info_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module to list family info of a given process PID");
