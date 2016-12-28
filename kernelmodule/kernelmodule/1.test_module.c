#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
MODULE_LICENSE("GPL");

int module_start(void)
{
        printk(" hello!!! \n");

            return -EBUSY;
}
void module_end(void)
{
}
module_init( module_start );
module_exit( module_end );
