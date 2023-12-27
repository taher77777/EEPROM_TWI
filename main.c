#include "STD_TYPE.h"
#include "PORT_interface.h"
#include "TWI_interface.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "EEPROM_interface.h"
#include "util/delay.h"


void main()
{
	//u8 Local_u8ReceivedData=1;
		PORT_voidInit();
		USART_voidInit();
		TWI_voidInitMaster(129);
		USART_voidSend('1');
		u8 count=0;
		u8 arr[16]="tahermohamedNTIi";
		u8 arr1[16]={0};
		EEPROM_voidSendDataPage16Byte(60, arr);
		_delay_ms(1000);
		EEPROM_u8ReadDataSEQUENTIAL(60,arr1);
		_delay_ms(1000);

	while(1)
	{
		USART_voidSend(arr1[count]);
		_delay_ms(1000);
		count++;
		if(count==15)
		{
			count=0;
		}

	}
}
