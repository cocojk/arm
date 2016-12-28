//mymodule.c

#include <linux/module.h>
#include <linux/kernel.h>
#include "header.h"

void do_module_func(void)
{
        printk(KERN_INFO "module_func\n");
}

static int mymodule_init(void)
{
        printk(KERN_INFO "Hello world\n");
            do_other_func();
                return 0;
}
module_init(mymodule_init);


static void mymodule_exit(void)
{
        printk(KERN_INFO "Goodbye, cruel world\n");
}
module_exit(mymodule_exit);

MODULE_LICENSE("GPL");
