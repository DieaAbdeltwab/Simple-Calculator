/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of LCD ************************************************************************************/
/***************** Date : 10/9/2022  ****************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : LCD ****************************************************************************************/
/****************************************************************************************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"DIO_interface.h"


#include"LCD_interface.h"
#include"LCD_config.h"
#include"LCD_private.h"


void LCD_voidInit(void)
{
	DIO_voidSetPortDirection(LCD_u8_DATA_PORT,0xFF);
	DIO_voidSetPinDirection(LCD_u8_CONTRAL_PORT,LCD_u8_RS_PIN,HIGH);
	DIO_voidSetPinDirection(LCD_u8_CONTRAL_PORT,LCD_u8_RW_PIN,HIGH);
	DIO_voidSetPinDirection(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	_delay_ms(35);
    LCD_voidSendCmnd(LCD_FUN_SIT);
	_delay_ms(1);
	LCD_voidSendCmnd(LCD_DISPLAY_ON_OF_CONTROL);
	_delay_ms(1);
	LCD_voidSendCmnd(LCD_DISPLAY_CLEAR);
	_delay_ms(2);

}

void LCD_voidSendCmnd(u8 Copy_u8Comnd)
{
	DIO_voidSetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RS_PIN,LOW);
	DIO_voidSetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RW_PIN,LOW);
	DIO_voidSetPortValue(LCD_u8_DATA_PORT,Copy_u8Comnd);
	DIO_voidSetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,LOW);
}
void LCD_voidSendChar(u8 Copy_u8Char)
{
	DIO_voidSetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RS_PIN,HIGH);
	DIO_voidSetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_RW_PIN,LOW);
	DIO_voidSetPortValue(LCD_u8_DATA_PORT,Copy_u8Char);
	DIO_voidSetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,HIGH);
	_delay_us(1);
	DIO_voidSetPinValue(LCD_u8_CONTRAL_PORT,LCD_u8_E_PIN,LOW);
}
void LCD_voidSendString(u8 *Copy_pu8String)
{
	for(int i=0; Copy_pu8String[i] != '\0' ; i++)
		  LCD_voidSendChar(Copy_pu8String[i]);

}
void LCD_voidSendNumber(u32 Copy_u8Number)
{
	u32 Local_remainder=0,Local_reverse=0,Local_TMP=0,Local_Counter,Local_TMPNum=Copy_u8Number;
	if (Copy_u8Number==0)
	{

		LCD_voidSendChar('0');
	}
	else
	{
	for(Local_Counter=-1;0==Local_TMP;Local_Counter++)
	{
	     Local_TMP=Local_TMPNum %10;
	     Local_TMPNum=Local_TMPNum / 10;
	}
	while(Copy_u8Number!=0)
	{
		Local_remainder=Copy_u8Number %10;
		Local_reverse=Local_reverse*10+Local_remainder;
		Copy_u8Number=Copy_u8Number / 10;
	}
	Local_TMP=0;
	while (Local_reverse!=0)
	{
		Local_TMP=Local_reverse%10;
		LCD_voidSendChar(Local_TMP+'0');
		Local_reverse=Local_reverse / 10;
	}
	while(0 != Local_Counter)
	{
		LCD_voidSendChar('0');

		Local_Counter--;
	}
	}
}
void LCD_vidGoToXY(u8 Copy_u8Location,u8 Copy_u8LineNum)
{
    switch (Copy_u8LineNum)
    {
          case 0 : LCD_voidSendCmnd(0x80+Copy_u8Location); break;
          case 1 : LCD_voidSendCmnd(0xC0+Copy_u8Location); break;
    }
}

void LCD_voidWriteSpicalCaracter(u8 Copy_u8PatternNumper,u8* Copy_u8Patterns){
	u8 Local_u8CGRAMAddress=0,Local_u8Iterator;
	Local_u8CGRAMAddress=Copy_u8PatternNumper*8;
	LCD_voidSendCmnd(Local_u8CGRAMAddress+64);
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		LCD_voidSendChar(Copy_u8Patterns[Local_u8Iterator]);
	}
}

void LCD_voidClear(void)
{
	  LCD_voidSendCmnd(LCD_CLEAR);
	  _delay_ms(2);
}

