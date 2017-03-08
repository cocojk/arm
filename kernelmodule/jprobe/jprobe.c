#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kprobes.h>
MODULE_LICENSE("GPL");

//잠시 바꿔치기할 함수입니다.
static void irq_hack(void)
{
    printk("i`m jprobe\n");

    jprobe_return();
}

// jprobe 생성
static struct jprobe my_probe =
{
    .entry = (kprobe_opcode_t *)irq_hack //바꿔치기할 함수 주소등록
};


int module_start(void)
{
    int 
    printk("jprobe module_start \n");
    my_probe.kp.symbol_name = "vector_irq";  //확인 할 함수를 이름

        do{
            if( (register_jprobe(&my_probe)) < 0 )       //jprobe 등록
            {
                
                printk("oop`s! \n");
            }
        }while( 0 );
    
   
    return 0;
}

void module_end(void)
{
    unregister_jprobe(&my_probe);               //jprbe 해제
}

module_init(module_start);
module_exit(module_end);
