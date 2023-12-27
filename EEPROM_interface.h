/*****************************************************************/
/*****************************************************************/
/********************		Author: Taher Mohamed	**************/
/********************		Layer: HAL				**************/
/********************		SWC: EEPROM				**************/
/********************		Version: 1.00			**************/
/********************		Date: 13-10-2020		**************/
/*****************************************************************/
/*****************************************************************/

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);

void EEPROM_voidSendDataPage16Byte(u16 Copy_u16LocationAddress, u8 Copy_u8ArrData16Byte[]);

void EEPROM_u8ReadDataSEQUENTIAL(u16 Copy_u16LocationAddress,u8 Copy_u8ArrData16Byte[]);

#endif
