#include "STD_TYPE.h"
#include "BIT_MATH.h"

#include "USART_register.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

/*Global pointer to function to hold receive ISR address*/
void (*USART_pvReceiveFunc)(u8 copy_u8received)=NULL;

void USART_voidInit(void)
{
	if (INTERRUPT==UART_WITH_INTERRUPT)
	{
		u8 Local_u8UCSRCValue=0;
		/*open interrupt to Receive Complete */
		SET_BIT(UCSRB,UCSRB_RXCIE);
		/*open interrupt to transmit Complete */
		SET_BIT(UCSRB,UCSRB_TXCIE);

		//****** we cannot use get and set bit with ucsrc we will create variable help us ****//

		//to use UCSRC
		SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);

		//set to 8 bit send and receive
		CLR_BIT(UCSRB,UCSRB_UCSZ2);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
		SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);

		/* mode select
		 	 	 	      1-Synchronous
		 	 	 	      2-ASynchronous */
		//ASynchronous
		CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);

		// now will set this value in UCSRC at same time
		UCSRC=Local_u8UCSRCValue;

		//boudrate now 9600 with 8Mhz
		UBRRL=UART_BOUDRATE;

		//enable pins recieve & transmit
		SET_BIT(UCSRB,UCSRB_TXEN);
		SET_BIT(UCSRB,UCSRB_RXEN);

	}
	else if (INTERRUPT==UART_WITHOUT_INTERRUPT)
	{
	/*we can not use set bit or clr bit here because it want in same time so we will creat a variable*/
	u8 Local_u8UCSRCValue=0;
	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);  //to use UCSRC
	//set to 8 bit send and receive
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);
	// now will set this value in UCSRC at same time
	UCSRC=Local_u8UCSRCValue;
	//boudrate now 9600 with 8Mhz
	UBRRL=UART_BOUDRATE;
	
	//enable
	SET_BIT(UCSRB,UCSRB_TXEN);   //tx enable
	SET_BIT(UCSRB,UCSRB_RXEN);   //rx enable
	}
}


//function to receive data no 8bit
u8 USART_u8Receive(void)
{
	//wait until be low by default it high when receive become low
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	//return the receive data
	return UDR;
}

void USART_voidSend(u8 Copy_u8data)
{
	//wait until transmit data empty
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR=Copy_u8data;   //transmit data
}

void UART_voidSendNumber(u8 Copy_u8number)
{

	switch(Copy_u8number)
	{
	case 0 :USART_voidSend('0');break;
	case 1 :USART_voidSend('1'); break;
	case 2 :USART_voidSend('2') ; break;
	case 3 :USART_voidSend('3') ; break;
	case 4 :USART_voidSend('4') ; break;
	case 5 :USART_voidSend('5') ; break;
	case 6 :USART_voidSend('6') ; break;
	case 7 :USART_voidSend('7') ; break;
	case 8 :USART_voidSend('8') ; break;
	case 9 :USART_voidSend('9') ; break;
	}

}

//send string
void USART_voidSendString(u8 *str)
{
        u8 i;
        for(i=0;i<100;i++) {
                if((*(str+i))=='\0')
                        {break;}
                USART_voidSend(*(str+i));
               // UDR=*(str+i);
        }
}

//get string
void UARTGetString(u8 *str)  //Receive a character until carriage return or newline
{
	u8 i = 0;
	str[i] = USART_u8Receive();
	while(str[i] != '\n')
	{
		i++;
		str[i] = USART_u8Receive();
	}
	str[i] = '\0';
}

void UART_voidDisplayNumber(u16 Copy_u8Number)
{
	u8 Local_u8Itrator=0,Local_u8State=0,Digit[4]={0};
	Digit[3]=Copy_u8Number%10;
	Copy_u8Number=Copy_u8Number/10;
	Digit[2]=Copy_u8Number%10;
	Copy_u8Number=Copy_u8Number/10;
	Digit[1]=Copy_u8Number%10;
	Copy_u8Number=Copy_u8Number/10;
	Digit[0]=Copy_u8Number%10;

	for(Local_u8Itrator=0;Local_u8Itrator<4;Local_u8Itrator++)
	{
		if(Digit[Local_u8Itrator]>0)
		{
			Local_u8State=1;
		}
		if (Local_u8State==0)
		{
			UART_voidSendNumber(Digit[Local_u8Itrator]);
/*		switch(Digit[Local_u8Itrator])
		{

		case 1:UART_voidSendNumber(1);break;
		case 2:UART_voidSendNumber(2);break;
		case 3:UART_voidSendNumber(3);break;
		case 4:UART_voidSendNumber(4);break;
		case 5:UART_voidSendNumber(5);break;
		case 6:UART_voidSendNumber(6);break;
		case 7:UART_voidSendNumber(7);break;
		case 8:UART_voidSendNumber(8);break;
		case 9:UART_voidSendNumber(9);break;
		}*/
		}
		else
		{
			UART_voidSendNumber(Digit[Local_u8Itrator]);
/*			switch(Digit[Local_u8Itrator])
			{
			case 0:CLCD_voidSendData('0');break;
			case 1:CLCD_voidSendData('1');break;
			case 2:CLCD_voidSendData('2');break;
			case 3:CLCD_voidSendData('3');break;
			case 4:CLCD_voidSendData('4');break;
			case 5:CLCD_voidSendData('5');break;
			case 6:CLCD_voidSendData('6');break;
			case 7:CLCD_voidSendData('7');break;
			case 8:CLCD_voidSendData('8');break;
			case 9:CLCD_voidSendData('9');break;
			}*/
		}

	}
	}

/*part of interrupt*/

void USART_voidRecieveSetCallBack(void (*Copy_pvRecieveFunc)(u8 copy_u8received))
{
	USART_pvReceiveFunc=Copy_pvRecieveFunc;
}


void __vector_13 (void)  __attribute__((signal));
void __vector_13 (void)
{
	if(USART_pvReceiveFunc != NULL)
	{
		USART_pvReceiveFunc(UDR);
	}
	else
	{
		/*Do nothing*/
	}
}


