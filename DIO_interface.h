/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Interface of DIO  *********************************************************************************/
/***************** Date : 3/9/2022  *****************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : Drive For DIO ******************************************************************************/
/****************************************************************************************************************************/

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/* Macros for PORTS */
#define DIO_u8_PORTA             0
#define DIO_u8_PORTB             1
#define DIO_u8_PORTC             2
#define DIO_u8_PORTD             3

/* Macros for PINS */
#define DIO_u8_PIN0              0
#define DIO_u8_PIN1              1
#define DIO_u8_PIN2              2
#define DIO_u8_PIN3              3
#define DIO_u8_PIN4              4
#define DIO_u8_PIN5              5
#define DIO_u8_PIN6              6
#define DIO_u8_PIN7              7

/* Macros for Pin Direction */
#define DIO_u8_PIN_OUTPUT            1
#define DIO_u8_PIN_INPUT             0

#define DIO_u8_PORT_OUTPUT            0xFF
#define DIO_u8_PORT_INPUT             0x00

/* Macros for Pin Value */
#define HIGH              1
#define LOW               0


void DIO_voidSetPinDirection(u8 Copy_U8Port , u8 Copy_U8Pin ,u8 Copy_U8Dir);
void DIO_voidSetPinValue(u8 Copy_U8Port , u8 Copy_U8Pin ,u8 Copy_U8Dir);
u8 DIO_u8GetPinValue(u8 Copy_U8Port , u8 Copy_U8Pin);
void DIO_voidTogglePinValue(u8 Copy_U8Port , u8 Copy_U8Pin);
void DIO_voidSetPortDirection(u8 Copy_U8Port , u8 Copy_U8Dir);
void DIO_voidSetPortValue(u8 Copy_U8Port , u8 Copy_U8Dir);

#endif
