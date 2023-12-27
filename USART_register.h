/*****************************************************************/
/*****************************************************************/
/********************		Author: TAHER MOHAMED	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: USART				**************/
/********************		Version: 1.00			**************/
/********************		Date: 28-8-2020			**************/
/*****************************************************************/
/*****************************************************************/

#ifndef USART_REGISTER_H_
#define USART_REGISTER_H
#define UDR       			*((volatile u8*)0x2C)				//send (when write ) and recieve (when read) data 

#define UCSRA     			*((volatile u8*)0x2B)				//usart control and state register A
#define UCSRA_RXC			7									//This flag bit is set when data in the receive buffer 
#define UCSRA_TXC			6									//This flag bit is set when data Transmit Complete
#define UCSRA_UDRE			5									//The UDRE Flag indicates if the transmit buffer (UDR) is ready to receive
#define UCSRA_FE			4
#define UCSRA_DOR			3
#define UCSRA_PE			2
#define UCSRA_U2X			1
#define UCSRA_MPCM			0

#define UCSRB     			*((volatile u8*)0x2A)				//usart control and state register B
#define UCSRB_RXCIE			7									//RX Complete Interrupt Enable
#define UCSRB_TXCIE			6									//TX Complete Interrupt Enable
#define UCSRB_UDRIE			5								    //Data Register Empty Interrupt Enable
#define UCSRB_RXEN			4								    //Receiver Enable
#define UCSRB_TXEN			3								    //Transmitter Enable
#define UCSRB_UCSZ2			2								    //Character Size
#define UCSRB_RXB8			1									//Receive Data Bit 8
#define UCSRB_TXB8			0									//Transmit Data Bit 8

#define UCSRC     			*((volatile u8*)0x40)				//usart control and state register A 
#define UCSRC_URSEL			7								    //The URSEL must be one when writing the UCSRC
#define UCSRC_UMSEL			6									//Mode Select
#define UCSRC_UPM1			5									//
#define UCSRC_UPM0			4
#define UCSRC_USBS			3									//Stop Bit Select
#define UCSRC_UCSZ1			2									//Character Size
#define UCSRC_UCSZ0     	1									//Character Size
#define UCSRC_UCPOL			0									

//Baud Rate Registers
#define UBRRL     			*((volatile u8*)0x29)				//0 to 7
#define UBRRH     			*((volatile u8*)0x40)				//8 to 11
#define UBRRH_URSEL         7									//Bit Select register

#endif