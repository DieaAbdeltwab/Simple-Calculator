/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of KPD ************************************************************************************/
/***************** Date : 9/9/2022  *****************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : Drive For KPD ******************************************************************************/
/****************************************************************************************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#define F_CPU 8000000UL
#include <util/delay.h>
/* MCAL */
#include"DIO_interface.h"
/* HAL */
#include"KPD_interface.h"
#include"KPD_private.h"
#include"KPD_config.h"


const u8 KPD_Au8Keys[4][4]= KPD_KEYS;
const u8 KPD_Au8RowsPins[4]={KPD_u8_R1_PIN,KPD_u8_R2_PIN,KPD_u8_R3_PIN,KPD_u8_R4_PIN};
const u8 KPD_Au8ColsPins[4]={KPD_u8_C1_PIN,KPD_u8_C2_PIN,KPD_u8_C3_PIN,KPD_u8_C4_PIN};


void KPD_voidInit(void)
{
	DIO_voidSetPortDirection(KPD_u8_PORT,0b11110000);
	DIO_voidSetPortValue(KPD_u8_PORT,0b11111111);
}

u8 KPD_u8GetPressdKey_IMT(void)
{
	u8 Local_Pessed,Local_Key;
	Local_Key=KPD_u8_KEY_NOT_PRESSED;
	for(int Local_u8ColsCounter=0;Local_u8ColsCounter<4;Local_u8ColsCounter++)
	{
		DIO_voidSetPinValue(KPD_u8_PORT,Local_u8ColsCounter+4,LOW);
		for(int Local_u8RowsCounter=0;Local_u8RowsCounter<4;Local_u8RowsCounter++)
		{
			
			Local_Pessed=DIO_u8GetPinValue(KPD_u8_PORT,Local_u8RowsCounter);
			if(Local_Pessed==LOW)
			{
				Local_Key=4*Local_u8RowsCounter+Local_u8ColsCounter;
				while(Local_Pessed==LOW)
				   Local_Pessed=DIO_u8GetPinValue(KPD_u8_PORT,Local_u8RowsCounter);
				_delay_ms(5);
			}	
		}
		DIO_voidSetPinValue(KPD_u8_PORT,Local_u8ColsCounter+4,HIGH);
	}
	return Local_Key;	
}
u8 KPD_u8GetKeyState_HC_543(void)
{
	u8 Local_Pressed,Local_Key;
	Local_Key=KPD_u8_KEY_NOT_PRESSED;
	for(int Local_u8ColsCounter=0;Local_u8ColsCounter<4;Local_u8ColsCounter++)
	{
		DIO_voidSetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8ColsCounter],LOW);
		for(int Local_u8RowsCounter=0;Local_u8RowsCounter<4;Local_u8RowsCounter++)
		{

			Local_Pressed=DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8RowsPins[Local_u8RowsCounter]);
			if(Local_Pressed==LOW)
			{
				Local_Key=KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
				while(Local_Pressed==LOW)
				   Local_Pressed=DIO_u8GetPinValue(KPD_u8_PORT,KPD_Au8RowsPins[Local_u8RowsCounter]);
				_delay_ms(10);
			}
		}
		DIO_voidSetPinValue(KPD_u8_PORT,KPD_Au8ColsPins[Local_u8ColsCounter],HIGH);
	}
	return Local_Key;
}

