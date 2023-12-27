/*********************************************************/
/***********		Author: TAHER MOHAMED 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: CLCD 		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 14-8/2020		 	**************/
/*********************************************************/
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include<util/delay.h>
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"


void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*Set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);

	/*Set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set command to data pins*/
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN,GET_BIT(Copy_u8Command,7));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN,GET_BIT(Copy_u8Command,6));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN,GET_BIT(Copy_u8Command,5));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN,GET_BIT(Copy_u8Command,4));
	

	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	/*Set RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);

	/*Set RW pin to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);

	/*Set Data to data pins*/
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN,GET_BIT(Copy_u8Data,7));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN,GET_BIT(Copy_u8Data,6));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN,GET_BIT(Copy_u8Data,5));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN,GET_BIT(Copy_u8Data,4));


	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

	/*Set Data to data pins*/
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN,GET_BIT(Copy_u8Data,3));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN,GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN,GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN,GET_BIT(Copy_u8Data,0));
	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);
}
void CLCD_voidSendString(const char * Copy_pcString)
{
	u8 Local_count=0;
	while(Copy_pcString[Local_count]!='\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_count]);
		Local_count++;
	}
}

void CLCD_voidInit(void)
{
	/*Wait for more than 30 ms*/
	_delay_ms(40);

	/*Function set command: 2 lines, 5*8 Font size*/
	CLCD_voidSendCommand(0b00100000);
	CLCD_voidSendCommand(0b00100000);
	CLCD_voidSendCommand(0b10000000);


	/*Display on off control: display enable, disable cursor, no blink cursor*/
	CLCD_voidSendCommand(0b00000000);
	CLCD_voidSendCommand(0b11000000);

	/*Clear display*/
	CLCD_voidSendCommand(0b00000000);
	CLCD_voidSendCommand(0b00010000);
}
/*to write in certin position in LCD*/
void CLCD_voidGoToxy(u8 Copy_u8posx,u8 Copy_u8posy)
{
	u8 Local_u8address;
	if(Copy_u8posx==0)
		Local_u8address=Copy_u8posy;
	if(Copy_u8posx==1)
			Local_u8address=Copy_u8posy+0x40;
	Local_u8address=Local_u8address+128;
	CLCD_voidSendCommand(Local_u8address);
	CLCD_voidSendCommand((Local_u8address<<4));

}
void CLCD_voidWriteSpecialCharacter(u8 * Copy_pu8Pattern,u8 Copy_PatternNumber,u8 Copy_u8posx,u8 Copy_u8posy)
{
	
	u8 LOcal_u8CGRAMAddress=0,Local_u8Iterator;
	/*Calculate cGRam address whose each block is 8 bytes*/
	LOcal_u8CGRAMAddress=Copy_PatternNumber*8;
	
	/* Send CG Ram address command to LCD ,with setting  bit 6*/
	LOcal_u8CGRAMAddress=LOcal_u8CGRAMAddress+64;
	CLCD_voidSendCommand(LOcal_u8CGRAMAddress);
	CLCD_voidSendCommand((LOcal_u8CGRAMAddress<<4));
	/* Write pattern in CG Ram */
	 
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}
	/* go back to DDRAM to display the pattrn*/
	CLCD_voidGoToxy(Copy_u8posx,Copy_u8posy);
	/*Display the pattern write in CGRAM*/
	CLCD_voidSendData(Copy_PatternNumber);
	
}
void CLCD_voidDisplayNumber(u16 Copy_u8Number)
{

	u8 Local_u8Itrator=0,Local_u8State=0,Digit[4]={0};
	if(Copy_u8Number==0)
	{
	CLCD_voidSendData('0');
	}
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
		switch(Digit[Local_u8Itrator])
		{
		case 1:CLCD_voidSendData('1');break;
		case 2:CLCD_voidSendData('2');break;
		case 3:CLCD_voidSendData('3');break;
		case 4:CLCD_voidSendData('4');break;
		case 5:CLCD_voidSendData('5');break;
		case 6:CLCD_voidSendData('6');break;
		case 7:CLCD_voidSendData('7');break;
		case 8:CLCD_voidSendData('8');break;
		case 9:CLCD_voidSendData('9');break;
		}
		}
		else
		{
			switch(Digit[Local_u8Itrator])
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
			}
		}

	}
	}
	
void CLCD_voidClearDisplay(void)
{
	CLCD_voidSendCommand(0b00000000);
	CLCD_voidSendCommand(0b00010000);
	
}



