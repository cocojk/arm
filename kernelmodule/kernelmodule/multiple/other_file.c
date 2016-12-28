//other_file.c

#include "header.h"
#include <linux/kernel.h>

void do_other_func(void)
{
    printk(KERN_INFO "other_func\n");
    do_module_func();
}
