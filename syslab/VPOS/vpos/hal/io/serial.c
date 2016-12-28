#include "serial.h"
#include "vh_cpu_hal.h"
#include "vh_variant_hal.h"
#include "vh_io_hal.h"
#include "dd.h"
#include "printk.h"


static SERIAL_QUEUE queue;
static int kIsQueueEmpty(SERIAL_QUEUE* pstQueue);
static int kIsQueueFull(SERIAL_QUEUE* pstQueue); 
static int kPutQueue(SERIAL_QUEUE* pstQueue,char pvData);
static int kGetQueue(SERIAL_QUEUE* pstQueue,char* pvData);


void vh_serial_interrupt_handler(void);


static int kIsQueueFull(SERIAL_QUEUE* pstQueue)
{

	if((pstQueue->pop_idx==pstQueue->push_idx)&&(pstQueue->lastOperationPush==1))
	{
		return 1;
	}
	return 0;

}
// 큐가 비었는지 여부를 반환
static int kIsQueueEmpty(SERIAL_QUEUE* pstQueue)
{
	// 큐의 삽입 인덱스와 제거 인덱스가 같고 마지막으로 수행된 명령이 제거이면 큐가 비었으므로 제거할 수 없음
	if((pstQueue->pop_idx==pstQueue->push_idx)&&(pstQueue->lastOperationPush==0))
	{
		return 1;
	}
	return 0;
}

// 큐에 데이터를 삽입 
static int kPutQueue(SERIAL_QUEUE* pstQueue,char pvData)
{
	if(kIsQueueFull(pstQueue)==1)
	{
		return 0;
	}


	pstQueue->buffer[pstQueue->push_idx]=pvData;

	// 삽입 인덱스를 변경하고 삽입 동작을 수행했음을 기록
	pstQueue->push_idx=(pstQueue->push_idx+1)%pstQueue->maxCount;
	pstQueue->lastOperationPush=1;
	return 1;
}

// 큐에서 데이터를 제거
static int kGetQueue(SERIAL_QUEUE* pstQueue,char* pvData)
{
	// 큐가 비었으면 제거할 수 없음
	if(kIsQueueEmpty(pstQueue)==1)
	{
		return 0;
	}

	*pvData = pstQueue->buffer[pstQueue->pop_idx];

	// 제거 인덱스 변경하고 제거 동작을 수행했음을 기록
	pstQueue->pop_idx=(pstQueue->pop_idx+1)%pstQueue->maxCount;
	pstQueue->lastOperationPush=0;;
	return 1;
}



char getc(void)
{
	char c;
/*	unsigned long rxstat;

	while(!vh_SERIAL_CHAR_READY());

	c = vh_SERIAL_READ_CHAR();
	rxstat = vh_SERIAL_READ_STATUS();
*/
	while(!kGetQueue(&queue,&c)){
	}

	return c;
}

void putc(char c)
{
	vh_SERIAL_PUTC(c);
}

int tstc()
{
	return vh_SERIAL_CHAR_READY();
}


void vh_serial_init(void)
{
	
	int i;
	// UART 1 Setting
	// UART 1 GPIO setting 
	vh_GPA0CON = vh_vSERIAL_CON;
	vh_GPA0PULL = vh_vSERIAL_PULL;

	// UART 1 Configuration 
	vh_ULCON1 = vh_vSERIAL_ULCON;
	vh_UCON1 = vh_vSERIAL_UCON;
	vh_UFCON1 = vh_vSERIAL_UFCON;
	vh_UINTM1 = vh_vSERIAL_UINTM;
	vh_UINTP1 = vh_vSERIAL_UINTP;
	vh_UBRDIV1 = ((66000000/(115200*16))-1);

	// queue initialize 
	queue.buffer = serial_buff;
	queue.maxCount = SERIAL_BUFF_SIZE;
	queue.push_idx = 0;
	queue.pop_idx = 0;
	queue.lastOperationPush = 0;
	
	for(i=0;i<SERIAL_BUFF_SIZE;i++)	serial_buff[i] = '\0';

	
}

void vh_serial_irq_enable(void)
{
	/* enable UART1 Interrupt */
	vh_VIC1VECTADDR11 = (unsigned int)&vh_serial_interrupt_handler;
	vh_VIC1INTENABLE |= vh_VIC_UART1_bit;
	vh_VIC1INTSELECT &= ~vh_VIC_UART1_bit;
	vh_VIC1SWPRIORITYMASK = 0xffff;
}

void vk_serial_push(void)
{
	char c;
	int i=0;
	c = vh_URXH1;
	kPutQueue(&queue,c);

}

void vh_serial_interrupt_handler(void)
{
	vk_serial_push();
	vh_VIC1INTENCLEAR |= vh_VIC_UART1_bit;
	vh_VIC1INTENABLE |= vh_VIC_UART1_bit;
	vh_UINTP1 = 0xf;
}
