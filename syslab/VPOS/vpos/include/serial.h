#ifndef __SERIAL_H__
#define __SERIAL_H__

#define SERIAL_BUFF_SIZE	100

void putc(char c);
char getc(void);
#ifndef MYSEO
int tstc(void);
#endif
void vh_serial_init(void);
void vh_serial_irq_enable(void);

char serial_buff[SERIAL_BUFF_SIZE];


typedef struct QueueStruct
{
	char* buffer;

	int maxCount;

	unsigned int push_idx;
	unsigned int pop_idx;

	// 1 push 0 pop 
	int lastOperationPush;
} SERIAL_QUEUE;

#endif /* __SERIAL_H__ */
