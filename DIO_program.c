/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Program of DIO  ***********************************************************************************/
/***************** Date : 3/9/2022  *****************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : Drive For DIO ******************************************************************************/
/****************************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"
void DIO_voidSetPinDirection(u8 Copy_U8Port ,u8 Copy_U8Pin,u8 Copy_U8Dir)
{
	
	if(1==Copy_U8Dir)
	{
	    switch (Copy_U8Port)
		{
		  case 0: SET_BIT(DDRA,Copy_U8Pin); break;
		  case 1: SET_BIT(DDRB,Copy_U8Pin); break;
		  case 2: SET_BIT(DDRC,Copy_U8Pin); break;
		  case 3: SET_BIT(DDRD,Copy_U8Pin); break;
		}
	}
	else if (0==Copy_U8Dir)
	{
		switch (Copy_U8Port)
		{
		  case 0: ClER_BIT(DDRA,Copy_U8Pin); break;
		  case 1: ClER_BIT(DDRB,Copy_U8Pin); break;
		  case 2: ClER_BIT(DDRC,Copy_U8Pin); break;
		  case 3: ClER_BIT(DDRD,Copy_U8Pin); break;
		}	
	}
}
void DIO_voidSetPinValue(u8 Copy_U8Port ,u8 Copy_U8Pin,u8 Copy_U8Value)
{
		
	if(1==Copy_U8Value)
	{
	    switch (Copy_U8Port)
		{
		  case 0: SET_BIT(PORTA,Copy_U8Pin); break;
		  case 1: SET_BIT(PORTB,Copy_U8Pin); break;
		  case 2: SET_BIT(PORTC,Copy_U8Pin); break;
		  case 3: SET_BIT(PORTD,Copy_U8Pin); break;
		}
	}
	else if (0==Copy_U8Value)
	{
		switch (Copy_U8Port)
		{
		  case 0: ClER_BIT(PORTA,Copy_U8Pin); break;
		  case 1: ClER_BIT(PORTB,Copy_U8Pin); break;
		  case 2: ClER_BIT(PORTC,Copy_U8Pin); break;
		  case 3: ClER_BIT(PORTD,Copy_U8Pin); break;
		}	
	}
}
u8 DIO_u8GetPinValue(u8 Copy_U8Port ,u8 Copy_U8Pin)
{
		switch (Copy_U8Port)
		{
		  case 0: return GET_BIT(PINA,Copy_U8Pin); break;
		  case 1: return GET_BIT(PINB,Copy_U8Pin); break;
		  case 2: return GET_BIT(PINC,Copy_U8Pin); break;
		  case 3: return GET_BIT(PIND,Copy_U8Pin); break;
		}
}
void DIO_voidTogglePinValue(u8 Copy_U8Port ,u8 Copy_U8Pin)
{
	switch (Copy_U8Port)
	{
		  case 0: TOOGLE_BIT(PORTA,Copy_U8Pin); break;
		  case 1: TOOGLE_BIT(PORTB,Copy_U8Pin); break;
		  case 2: TOOGLE_BIT(PORTC,Copy_U8Pin); break;
		  case 3: TOOGLE_BIT(PORTD,Copy_U8Pin); break;
	}
}
void DIO_voidSetPortDirection(u8 Copy_U8Port ,u8 Copy_U8Dir)
{
	switch (Copy_U8Port)
	{
		  case 0: DDRA = Copy_U8Dir; break;
		  case 1: DDRB = Copy_U8Dir; break;
		  case 2: DDRC = Copy_U8Dir; break;
		  case 3: DDRD = Copy_U8Dir; break;

	}
}
void DIO_voidSetPortValue(u8 Copy_U8Port ,u8 Copy_U8Val)
{
	switch (Copy_U8Port)
	{
		  case 0: PORTA = Copy_U8Val; break;
		  case 1: PORTB = Copy_U8Val; break;
		  case 2: PORTC = Copy_U8Val; break;
		  case 3: PORTD = Copy_U8Val; break;

	}	
}
