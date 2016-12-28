#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include "hackingnum.h"

void vm_area_probe (long pid)
{
    struct task_struct    *task;
    struct mm_struct      *mm;
    struct vm_area_struct *mmap; 

    task = current;
    mm   = task->mm;
    mmap = mm->mmap;

    printk("task_id = %d\n",task->pid);
    printk("start_code = %8x ",mm->start_code);
    printk("end_code   = %8x\n",mm->end_code);
    printk("start_data = %8x ",mm->start_data);
    printk("end_data   = %8x\n",mm->end_data);
    printk("start_brk  = %8x ",mm->start_brk);
    printk("brk        = %8x\n",mm->brk);
    printk("start_stack= %8x\n",mm->start_stack);
    printk("arg_start  = %8x ",mm->arg_start);
    printk("arg_end    = %8x\n",mm->arg_end);
    printk("env_start  = %8x ",mm->env_start);
    printk("env_end    = %8x\n",mm->env_end);
    do
    {
        printk("vm_start = %8x ",mmap->vm_start);
        printk("vm_end   = %8x ",mmap->vm_end);
        printk("vm_area  = %8x\n",mmap->vm_end - mmap->vm_start);
    }while(mmap = mmap->vm_next);

}
