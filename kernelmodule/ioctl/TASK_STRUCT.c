#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include "hackingnum.h"

void task_struct_vmaddress (long pid)
{
    struct task_struct *task;

    printk("task_struct_vmaddress\n");
    /*
    for_each_process(task) {
        printk("%s[%d] vmadd : %8x\n",task->comm,task->tgid,task);
    }
    */
}
