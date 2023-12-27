/********************		Author: TAHER MOHAMED	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: USART				**************/
/********************		Version: 1.00			**************/
/********************		Date: 28-8-2020			**************/
/*****************************************************************/
/*****************************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit(void);               								//function to initial
void USART_voidSend(u8 Copy_u8data);     								//function to transmit data
u8 USART_u8Receive(void);                								//function to receive data
void USART_voidRecieveSetCallBack(void (*Copy_pvRecieveFunc)(u8 copy_u8received));	//function set call back
void USART_voidSendString(u8 *str);
void UART_voidDisplayNumber(u16 Copy_u8Number);
void UARTGetString(u8 *str);
void UART_voidSendNumber(u8 Copy_u8number);

#endif
