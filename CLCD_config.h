/*********************************************************/
/***********		Author: Taher Mohamed 	**************/
/***********		Layer: HAL			 	**************/
/***********		Component: CLCD 		**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 14-8/2020		 	**************/
/*********************************************************/

/*Preprocessor file guard*/
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/*--------------FOUR_MODE-------------*/
#define CLCD_CTRL_PORT		    DIO_u8PORTD
#define CLCD_DATA_PORT		    DIO_u8PORTD
#define CLCD_D7_PIN			DIO_u8PIN0
#define CLCD_D6_PIN			DIO_u8PIN1
#define CLCD_D5_PIN			DIO_u8PIN2
#define CLCD_D4_PIN			DIO_u8PIN3

#define CLCD_RS_PIN			DIO_u8PIN4
#define CLCD_RW_PIN			DIO_u8PIN5
#define CLCD_E_PIN			DIO_u8PIN6

#endif
