#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init module_start(void) {
    printk(KERN_INFO "Hello, kernel!\n");
    return 0;
}

static void __exit module_end(void) {
    printk(KERN_INFO "Goodbye, kernel!\n");
}

module_init(module_start);
module_exit(module_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux driver");
