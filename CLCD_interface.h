/*********************************************************/
/***********		Author: TAHER MOHAMED 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: CLCD 		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 14-8/2020		 	**************/
/*********************************************************/


/*Preprocessor file guard*/
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidInit(void);

void CLCD_voidSendString(const char * Copy_pcString);

void CLCD_voidGoToxy(u8 Copy_u8posx,u8 Copy_u8posy);

void CLCD_voidWriteSpecialCharacter(u8 * Copy_pu8Pattern,u8 Copy_PatternNumberu8 ,u8 Copy_u8posx,u8 Copy_u8posy);

void CLCD_voidDisplayNumber(u16 Copy_u8Number);

void CLCD_voidClearDisplay(void);


#endif
