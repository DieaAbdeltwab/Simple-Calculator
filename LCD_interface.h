/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Interface of LCD **********************************************************************************/
/***************** Date : 10/9/2022  *****************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : LCD ****************************************************************************************/
/****************************************************************************************************************************/
#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#define HIGH   1
#define LOW    0
void LCD_voidInit(void);
void LCD_voidSendCmnd(u8 Copy_u8Comnd);
void LCD_voidSendChar(u8 Copy_u8Char);
void LCD_voidSendString(u8 *Copy_pu8String);
void LCD_voidSendNumber(u32 Copy_u8Number);
void LCD_vidGoToXY(u8 Copy_u8Location,u8 Copy_u8LineNum);
void LCD_WriteSpicalCaracter(u8 Copy_u8PatternNumper,u8* Copy_u8Patterns);
void LCD_voidClear(void);

#endif
