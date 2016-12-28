#ifndef _vh_IO_HAL_H_
#define _vh_IO_HAL_H_





/*******************************************************************
	VIC - S5PC100
*******************************************************************/
#define vh_VIC0INTENABLE		(*(volatile unsigned *)0xe4000010)
#define vh_VIC0INTSELECT		(*(volatile unsigned *)0xe400000c)
#define vh_VIC0INTENCLEAR		(*(volatile unsigned *)0xe4000014)
#define vh_VIC0VECTADDR25		(*(volatile unsigned *)0xe4000164)
#define vh_VIC0SWPRIORITYMASK	(*(volatile unsigned *)0xe4000024)



// Specifies interrupt enable register 
// intEnable [31:0] read: 0 disables interrupt 1 enables interrupt 
// 					write: 0 no effect 1 enables interrupt 
// there is one bit of the register for each interrupt source 
#define vh_VIC1INTENABLE		(*(volatile unsigned *)0xe4100010)

// Specifies interrupt select register 
// intSelect [31:0] 0 IRQ interrupt 1 FIQ interrupt 

// there is one bit of the register for each interrupt source 
#define vh_VIC1INTSELECT		(*(volatile unsigned *)0xe410000c)

// Specifies interrupt enable clear 
// intEable Clear [31:0] 0 No effect 1 disable interrupt 
#define vh_VIC1INTENCLEAR		(*(volatile unsigned *)0xe4100014)

// Specifies vector address register 
// VectAddr [31:0] contains ISR vector addresses 
#define vh_VIC1VECTADDR11		(*(volatile unsigned *)0xe410012c)

// Specifies vector software priority mask register 
// VectPriority [15:0] controls software masking of the 16 interrupt priority levels
//						0 interrupt priority level is masked 1 not masked 
#define vh_VIC1SWPRIORITYMASK	(*(volatile unsigned *)0xe4100024)


#define vh_VIC_UART1			11
#define vh_VIC_UART1_bit		(1<<vh_VIC_UART1)

//Timer setting
#define vh_VIC_TIMER4 			25	
#define vh_VIC_TIMER4_bit 		(1<<vh_VIC_TIMER4)

/*******************************************************************
   	GPIO
 *******************************************************************/
#define vh_GPA0CON			(*(volatile unsigned *)0xE0300000)
#define vh_GPA0DAT			(*(volatile unsigned *)0xE0300004)
#define vh_GPA0PULL			(*(volatile unsigned *)0xE0300008)
#define vh_GPA0DRV			(*(volatile unsigned *)0xE030000c)

//
#define vh_GPJ2CON			(*(volatile unsigned *)0xe0300240)
#define vh_GPJ2DAT			(*(volatile unsigned *)0xe0300244)

//
/*****************************************************************
   Timer address
 #*****************************************************************/
// Reserved [31:24] Dead Zone length [23:16] 
// Prescalar1 [15:8] Prescalar0 [7:0]
// Prescalar1 = 132 -> 66,000,000 Hz -> 500,000 Hz
#define vh_vTimer_CFG0			0x8300

// Reserved [31:24] Divider MUX4 [19:16]
// Divider MUX3 [15:13] Divider MUX2 [11:8]
// Divider MUX1 [7:4] Divider MUX0 [3:0]
// Divider = 16 -> 500,000 Hz -> 31,250 Hz 
#define vh_vTimer_CFG1			0x4000

// Timer4 Auto Reload [22] = 0 
// Timer4 Manual Update [21] = 0 
// Timer4 Start/Stop [20] = 0
#define vh_vTimer_TCON_CLEAR4	0x00 

// Timer4 Auto Reload [22] = 1 
// Timer4 Manual Update [21] = 1 
// Timer4 Start/Stop [20] = 0
#define vh_vTimer_TCON_RELOAD_UPDATE 0x600000	

// Timer4 Auto Reload [22] = 1 
// Timer4 Manual Update [21] = 0 
// Timer4 Start/Stop [20] = 1
#define vh_vTimer_TCON_RELOAD_START	0x500000 

// TCNTB4 = 31,250 
#define vh_vTimer_TCNTB4		0x7A12



// Pulse Width Modulation Timer base address 
#define vh_PWM_BASE				0xEA000000

// Specifies Timer Configuration Register0 
#define vh_TCFG0				(*(volatile unsigned*)(vh_PWM_BASE+0x00))

// Specifies Timer Configuration Register1 
#define vh_TCFG1				(*(volatile unsigned*)(vh_PWM_BASE+0x04))

// Specifies Timer Control Register 
#define vh_TCON 				(*(volatile unsigned*)(vh_PWM_BASE+0x08))

// Specifies Timer Interrupt Control and Status Register 
#define vh_TINT_CSTAT			(*(volatile unsigned*)(vh_PWM_BASE+0x44))

// Specifies Timer 4 Count Buffer Register 
#define vh_TCNTB4 				(*(volatile unsigned*)(vh_PWM_BASE+0x3C))

// Specifies Timer 4 Count Observation Register 
#define vh_TCNTO4				(*(volatile unsigned*)(vh_PWM_BASE+0x40))


/******************************************************************
  	UART address
 ******************************************************************/

// value of GPA0 configuration register  
// GPA0CON[4] [19:16] UART_1_RXD 0010 
// GPA0CON[5] [23:20] UART_1_TXD 0010 
#define vh_vSERIAL_CON			0x220000 

// value of  GPA0 Pull register  
// GPA0PUD[4] [9:8] Enables Pull-up 10 
// GPA0PUD[5] [11:10] Enable Pull-up 10 
#define vh_vSERIAL_PULL			0xa00	//0xf00// Pull-up enable

// value of UART line control register 
// word length [1:0] 8bit 11 
#define vh_vSERIAL_ULCON		0x3	

// value of UART control register 
// Receive Mode  [1:0] interrupt request or polling mode 01 
// transmit mode [3:2] interrupt request or polling mode 01 
// Rx error status interrupt enable [6] 1 
// Rx interrupt type [8] pulse 0 
// Tx interrupt type [9] level 1 
// clock selection [11:10] pclk 00 
#define vh_vSERIAL_UCON			0x245

// value of UART fifo control register 
// FIFO enable [0] enable 1
// Rx FIFO reset [1] FIFO reset 1 
// Tx FIFO reset[2] FIFO reset 1 
// Rx FIFO Trigger Level [5:4] 1byte 00 
// Tx FIFO Trigger Level [7:8] 48byte 11 
#define vh_vSERIAL_UFCON		0xc7

// value of interrupt mask register 
// RXD [0] unmask 0 
// ERROR [1] mask 1 
// TXD [2] mask 1
// MODEM [3] mask 1
#define vh_vSERIAL_UINTM		0xE 

// value of interrupt pending register 
// RXD [0] generate 1
// ERROR [1] generate 1 
// TXD [2] generate 1 
// MODEM [3] generate 1 
#define vh_vSERIAL_UINTP		0xF 


#define vh_UART_CTL_BASE 		0xec000000	// UART 1 register base address

// Specifies line control register
#define vh_ULCON1	 		(*(volatile unsigned *)(vh_UART_CTL_BASE+0x400))	

// Specifies control register  
#define vh_UCON1	 			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x404))	

// Specifies fifo control register 
#define vh_UFCON1	 		(*(volatile unsigned *)(vh_UART_CTL_BASE+0x408))	

// Specifies modem control register 
#define vh_UMCON1	 		(*(volatile unsigned *)(vh_UART_CTL_BASE+0x040c))	

// Specifies Baud rate divisor register 
#define vh_UBRDIV1	 		(*(volatile unsigned *)(vh_UART_CTL_BASE+0x0428))	

// Specifies interrupt pending register 
#define vh_UINTP1			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x0430))

// Specifies interrupt source pending register 
#define vh_UINTSP1			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x0434))

// Specifies interrupt mask register 
#define vh_UINTM1			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x0438))

// Specifies Tx/Rx status register 
#define vh_UTRSTAT1			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x0410))

// Specifies Rx error status register 
#define vh_UERSTAT1			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x0414))

// Specifies fifo status register 
#define vh_UFSTAT1			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x0418))

// Specifies receive buffer register 
#define	vh_URXH1			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x0424))

// Specifies modem status register 
#define vh_UMSTAT1			(*(volatile unsigned *)(vh_UART_CTL_BASE+0x041C))

#define vh_vULCON                       0x3	// The number of data bits. 8-bit    
#define vh_vUCON                        0x245/* 0x745	 Receive mode	01 Interrupt request or polling mode
						Transmit mode	01 Interrupt request or polling mode
						Rx Error status Interrupt Enable 	1 Generates receive error status interrupt
						Tx Interrupt Type	1 Level*/
#define vh_UART_BAUD_RATE               115200
#define vh_UART_PCLK			66000000
#define vh_UART_BRD                     (((200*1000000) / (vh_UART_BAUD_RATE * 16)) - 1)	/* Baud rate division value
											DIV_VAL = (SCLK_UART / (bps * 16)) - 1
											115200 bps, SCLK_UART 40MHz */
#define vh_oUTRSTAT                    	0x10	// Specifies Tx/Rx status
#define vh_oUTXH                        0x0420	// Specifies transmit buffer
#define vh_oURXH                        0x24 	// Specifies receive buffer

#define vh_UTRSTAT_TX_EMPTY             (1 << 2)// Transmitter empty. if the transmit buffer has no valid data to transmit, then 1
#define vh_UTRSTAT_RX_READY             (1 << 0)// Receive buffer data ready. 1=buffer has a received data

/* UART Transmit Operation */
#define vh_SERIAL_WRITE_READY() 	((vh_UTRSTAT1) & vh_UTRSTAT_TX_EMPTY)
#define vh_UTXH1                        vk_REGb(vh_UART_CTL_BASE + (vh_oUTXH))
#define vh_SERIAL_WRITE_CHAR(c) 	((vh_UTXH1) = (c))
#define vh_SERIAL_PUTC(c)               ({while (!vh_SERIAL_WRITE_READY());vh_SERIAL_WRITE_CHAR(c);})

/* UART Receive OPeration */
#define vh_SERIAL_CHAR_READY()  	(vh_UTRSTAT1 & vh_UTRSTAT_RX_READY)
//#define vh_URXH1                        vk_REGb(vh_UART_CTL_BASE + (vh_oURXH))
#define vh_SERIAL_READ_CHAR()   	vh_URXH1

/************************************************************************************************/
#define vh_oUERSTAT				0x14	
#define vh_oURXHL				0x24	
#define vh_UERSTAT0				vh_bUART(0, vh_oUERSTAT)
#define vh_SERIAL_READ_STATUS()	(vh_UERSTAT0 & vh_UART_ERR_MASK) 
#define vh_UTXH0				vh_bUARTb(0, vh_oUTXHL)

#define vh_vUFCON				0x0
#define vh_vUMCON				0x0
#define vh_UART_ERR_MASK		0xF 

#define vh_bUART(x, Nb)			vk_REGl(vh_UART_CTL_BASE + (x)*0x4000 + (Nb))
#define vh_bUARTb(x, Nb)		vk_REGb(vh_UART_CTL_BASE + (x)*0x4000 + (Nb))

/*******************************************************************
   	nand flash address 
 *******************************************************************/
#define U8 		unsigned char
#define NAND_BASE 	0xe7200000

#define vh_rNFCONF 		(*(volatile unsigned *)(NAND_BASE+ 0x00))
#define vh_rNFCMD		(*(volatile U8*)(NAND_BASE + 0x04))
#define vh_rNFADDR 		(*(volatile U8*)(NAND_BASE + 0x08))
#define vh_rNFDATA		(*(volatile U8*)(NAND_BASE + 0x0c))
#define vh_rNFSTAT		(*(volatile unsigned *)(NAND_BASE + 0x10))
#define vh_rNFECC 		(*(volatile unsigned *)(NAND_BASE + 0x14))
#define vh_rNFECC0		(*(volatile U8 *)(NAND_BASE + 0x14))
#define vh_rNFECC1		(*(volatile U8 *)(NAND_BASE + 0x15))
#define vh_rNFECC2 		(*(volatile U8 *)(NAND_BASE + 0x16))

//NAND Flash Macro
#define NF_CMD(cmd) 		{vh_rNFCMD = cmd;}
#define NF_ADDR(addr) 		{vh_rNFADDR = addr;}
#define NF_nFCE_L() 		{vh_rNFCONF &=~(1 <<11);}
#define NF_nFCE_H() 		{vh_rNFCONF |= (1 <<11);}
#define NF_RSTECC()		{vh_rNFCONF |= (1 <<12);}
#define NF_RDDATA() 		(vh_rNFDATA)
#define NF_WRDATA(data) 	{vh_rNFDATA = data;}
#define NF_WAITRB() 		{while(!(vh_rNFSTAT&(1<<0)));}

// RnB Signal
#define NF_CLEAR_RB()           {vh_rNFSTAT |= (1<<2);}    // Have write '1' to clear this bit.
#define NF_DETECT_RB()          {while(!(vh_rNFSTAT&(1<<2)));}

#define NAND_CTL_S3C_WAIT 	0x100
/*****************************************************************************/

#endif  //_vh_IO_HAL_H_
