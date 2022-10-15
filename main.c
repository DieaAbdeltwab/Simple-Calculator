/****************************************************************************************************************************/
/***************** Author : Diea Abdeltwab **********************************************************************************/
/***************** File : Simple Calculator *********************************************************************************/
/***************** Date : 1/10/2022  ****************************************************************************************/
/***************** Version : 1.0  *******************************************************************************************/
/***************** Description : AVR Simple Calculator by ATMEGA 32 *********************************************************/
/**************************      IMT Embedded Systems AVR Course *************************************************************/
/****************************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
/***************************************************** Global **********************************************************/
/* ** Array to Save Numbers After to do Operations
   ** Calc_f64Numbers[0] =  Result for  Operation ** */
f64 Calc_f64Numbers[10]={0};
/* Array to Save Operations */
u16 Calc_u16Operations[10]={0};
/* Number of Input Number */
u8 Calc_u8CounterNumbers=0;
/* Number of Input Operations */
u8 Clac_u8CounterOperations=0;
/* IF ErrorFlag==1 Print Error*/
u8 Clac_u8ErrorFlag=0;
/* IF Clac_u8DeletFlag==0 user can Delete  , Clac_u8DeletFlag==1 user can not Delete */
u8 Clac_u8DeletFlag=0;
/* Counter for Each  Operations */
u8 Clac_u8MulCounter=0,Clac_u8DivCounter=0;
u8 Clac_u8AddCounter=0,Clac_u8SubCounter=0;
/* **Clac_u8FlagNumberOrOperation==1 User input number **
*  **Clac_u8FlagNumberOrOperation==0 User input Opration ** */
u8 Clac_u8FlagNumberOrOperation=1;
/* Cursor Position*/
u8 Clac_u8CursorPosition=0;
/* Counter for Operations without Number between them */
u8 Calc_u8CounterSeriesOperations=0;
/*********************************************************** Calculator Modes ***************************************/
void CALC_voidStart()
{
	LCD_voidSendString("   Calculator");
	_delay_ms(2000);
	LCD_voidClear();
}
/* After calculate result if user input C do this function */
void CALC_voidClearLCD()
{
	LCD_voidClear();
	LCD_voidSendString("Clearing LCD...");
	_delay_ms(2000);
	LCD_voidClear();
	/* Clear all Numbers and operations */
	for (u8 Local_u8Counter=0;Local_u8Counter<10;Local_u8Counter++)
	{
		Calc_f64Numbers[Local_u8Counter]=0;
		Calc_u16Operations[Local_u8Counter]=0;
	}
    Calc_u8CounterNumbers=0;
	Clac_u8CounterOperations=0;
	Clac_u8ErrorFlag=0;
	Clac_u8DeletFlag=0;
	Clac_u8CursorPosition=0;
	Clac_u8MulCounter=0;
	Clac_u8DivCounter=0;
	Clac_u8SubCounter=0;
	Clac_u8AddCounter=0;
	Clac_u8FlagNumberOrOperation=1;
	Calc_u8CounterSeriesOperations=0;
}
/* After calculate result if user input any Key else C do this function */
void CALC_voidUsedAns()
{
	LCD_voidClear();
	LCD_voidSendString("Ans");
	/* Clear all Numbers and operations But Not Delete Calc_f64Numbers[0] =  Result for last Operation */
	for (u8 Local_u8Counter=0;Local_u8Counter<10;Local_u8Counter++)
	{
		Calc_f64Numbers[Local_u8Counter+1]=0;
		Calc_u16Operations[Local_u8Counter]=0;
	}
    Calc_u8CounterNumbers=0;
	Clac_u8CounterOperations=0;
	Clac_u8ErrorFlag=0;
	Clac_u8DeletFlag=0;
	Clac_u8MulCounter=0;
	Clac_u8DivCounter=0;
	Clac_u8SubCounter=0;
	Clac_u8AddCounter=0;
	Clac_u8FlagNumberOrOperation=1;
	Calc_u8CounterSeriesOperations=0;
	Clac_u8CursorPosition=3;
}
/********************************************************** Delete ******************************************************/
/**                      If user input C Before =  do this function                                                    **/
void Calc_voidDelet (u8 Copy_Temp)
{
    /*  if last input was number delete this number */
	if (Clac_u8FlagNumberOrOperation==1 && Clac_u8DeletFlag==0)
	{
	    /* Clear this from LCD  */
        Clac_u8CursorPosition--;
        LCD_vidGoToXY(Clac_u8CursorPosition,0);
        LCD_voidSendChar(' ');
        /* Delete this number */
	    u32 Local_u32Temp = Calc_f64Numbers[Calc_u8CounterNumbers]/10;
	    Calc_f64Numbers[Calc_u8CounterNumbers]=Local_u32Temp;
	    /* User can not delete */
	    Clac_u8DeletFlag=1;
	}
	/*  if last input was operation delete all Last operations */
	else if (Clac_u8FlagNumberOrOperation==0 && Clac_u8DeletFlag==0)
	{
	    /* Clear this from operations  */
		for (u8 Local_u8Counter=1;Local_u8Counter<=Calc_u8CounterSeriesOperations && Clac_u8CursorPosition>0;Local_u8Counter++)
		{
		  Clac_u8CursorPosition--;
		  LCD_vidGoToXY(Clac_u8CursorPosition,0);
		  LCD_voidSendChar(' ');
		}
		/* If last input is * or / then - change number sign   */
		if (Clac_u8SubCounter==1)
		{
			 Calc_f64Numbers[Calc_u8CounterNumbers]*=-1;
		}
		/* Delete this operations */
		Calc_u16Operations[Clac_u8CounterOperations]=0;
		/*Init Counters*/
		Calc_u8CounterSeriesOperations=0;
		Clac_u8MulCounter=0;
		Clac_u8DivCounter=0;
		Clac_u8AddCounter=0;
		Clac_u8SubCounter=0;
		Clac_u8FlagNumberOrOperation=1;
		/* User can not delete */
		Clac_u8DeletFlag=1;
	}
}
/********************************************************** Logic of Calculator ***************************************************/
void Calc_voidLogicOfOperations(u8 Copy_u8Operation)
{
   Calc_u8CounterSeriesOperations++;
   switch(Copy_u8Operation)
   {
	case'*':
		  /* If user input * Check if he input + or - After it */
		  /**               3-*3=Error                        **/
		if (Clac_u8MulCounter!=0 || Clac_u8DivCounter!=0 || Clac_u8AddCounter!=0 || Clac_u8SubCounter!=0 )
		{
				    /* if last operation After * is + or  -  print Error */
					Clac_u8ErrorFlag=1;
		}
		else if(Clac_u8MulCounter==0)
		{
		/* if user just input * Store this operation */
		   Clac_u8MulCounter++;
		   Calc_u16Operations[Clac_u8CounterOperations]='*';
		}
    break;
    case '/':
        /* If user input / Check if he input + or - After it */
	    /**               3-/3=Error                        **/
		if (Clac_u8MulCounter!=0 || Clac_u8DivCounter!=0 || Clac_u8AddCounter!=0 || Clac_u8SubCounter!=0)
		{
		    /* If last operation After / is + or  -  print Error */
			Clac_u8ErrorFlag=1;
		}
		else if (Clac_u8DivCounter==0)
		{
		    /* If user just input / Store this operation */
			Clac_u8DivCounter++;
		    Calc_u16Operations[Clac_u8CounterOperations]='/';
		}

    break;
    case'+':
    	  Clac_u8AddCounter++;
          if (Clac_u8MulCounter==0 && Clac_u8DivCounter==0 && Clac_u8SubCounter==0)
          {
              /* If user just input + Store this operation */
    	      Calc_u16Operations[Clac_u8CounterOperations]='+';
          }
          else if (Clac_u8MulCounter>=1)
          {
            /* If user input + after * Store *        */
    	    Calc_u16Operations[Clac_u8CounterOperations]='*';
          }
          else if (Clac_u8DivCounter>=1)
          {
            /* If user input + after / Store /        */
    	    Calc_u16Operations[Clac_u8CounterOperations]='/';
          }
          else if (Clac_u8SubCounter>=1)
          {
            /* If user input + after - */
          	if (Clac_u8SubCounter==1 || Clac_u8SubCounter==3 || Clac_u8SubCounter==5)
          	{
          	     /* Store -  if number - is odd */
          	     Calc_u16Operations[Clac_u8CounterOperations]='-';
          	}
          	else if (Clac_u8SubCounter==2 || Clac_u8SubCounter==4 || Clac_u8SubCounter==6)
          	{
          	    /* Store +  if number - is even */
          	     Calc_u16Operations[Clac_u8CounterOperations]='+';
          	}
          }
    break;
    case'-':
    	Clac_u8SubCounter++;
        if (Clac_u8MulCounter==0 && Clac_u8DivCounter==0)
        {
            /* If user input -  */
        	if (Clac_u8SubCounter==1 || Clac_u8SubCounter==3 || Clac_u8SubCounter==5)
        	{
        	    /* Store -  if number - is odd */
                Calc_u16Operations[Clac_u8CounterOperations]='-';
        	}
        	else if (Clac_u8SubCounter==2 || Clac_u8SubCounter==4 || Clac_u8SubCounter==6)
        	{
        	    /* Store +  if number - is even */
                Calc_u16Operations[Clac_u8CounterOperations]='+';
        	}
        }
        else if (Clac_u8MulCounter>=1)
        {
           /* If user input - After  *   */
           if (Clac_u8SubCounter==1 || Clac_u8SubCounter==3 || Clac_u8SubCounter==5)
           {
               /* Change Last number sign*/
               /* If number - is even Last number sign is - */
        	   Calc_f64Numbers[Calc_u8CounterNumbers]*=-1;
           }
       	   else if (Clac_u8SubCounter==2 || Clac_u8SubCounter==4 || Clac_u8SubCounter==6)
       	   {
       	       /* Change Last number sign */
       	       /* If number - is even Last number sign is + */
       		   Calc_f64Numbers[Calc_u8CounterNumbers]*=-1;
       	   }
       	   /* Store *  */
  	       Calc_u16Operations[Clac_u8CounterOperations]='*';
        }
        else if (Clac_u8DivCounter>=1)
        {
            /* If user input - After  /   */
           if (Clac_u8SubCounter==1 || Clac_u8SubCounter==3 || Clac_u8SubCounter==5)
           {
               /* Change Last number sign*/
               /* If number - is even Last number sign is - */
        	   Calc_f64Numbers[Calc_u8CounterNumbers]*=-1;
           }
       	   else if (Clac_u8SubCounter==2 || Clac_u8SubCounter==4 || Clac_u8SubCounter==6)
       	   {
       	       /* Change Last number sign */
       	       /* If number - is even Last number sign is + */
       		   Calc_f64Numbers[Calc_u8CounterNumbers]*=-1;
       	   }
       	   /* Store /  */
  	       Calc_u16Operations[Clac_u8CounterOperations]='/';
        }
    break;
  }
}
void Calc_voidAllInputs (void)
{
	s16 Local_s16TempKey;
	while(1)
	{
	    /* Break this loop if user input = */
		Local_s16TempKey=KPD_u8GetKeyState_HC_543();
		if (Local_s16TempKey != KPD_u8_KEY_NOT_PRESSED)
		{
			if (Local_s16TempKey=='=')
			{
			    /*If user input = print = */
				LCD_vidGoToXY(Clac_u8CursorPosition,0);
				LCD_voidSendChar(Local_s16TempKey);
				Clac_u8CursorPosition++;
                /* Check last input was number */
				if ( Clac_u8MulCounter != 0 || Clac_u8SubCounter != 0 ||  Clac_u8DivCounter != 0 || Clac_u8AddCounter != 0 )
                {
                    /* if last input wast operation print Error*/
                    /**         3*-=Error                     **/
                    Clac_u8ErrorFlag=1;
                }
				break;
			}
			else if(Local_s16TempKey=='+' ||Local_s16TempKey=='-' ||Local_s16TempKey=='*' ||Local_s16TempKey=='/' )
			{
			    /* If user input operation print this operation*/
				LCD_vidGoToXY(Clac_u8CursorPosition,0);
				LCD_voidSendChar(Local_s16TempKey);
				Clac_u8CursorPosition++;
                /* Go to Function to calculate Logic Of Operations */
				Calc_voidLogicOfOperations(Local_s16TempKey);
				/* Last input was Operation*/
				Clac_u8FlagNumberOrOperation=0;
				/* User can delete */
				Clac_u8DeletFlag=0;
			}
			else if(Local_s16TempKey=='C')
			{
				if (Clac_u8CursorPosition>0)
                {
                    /* if user input C Delete last input */
                    Calc_voidDelet(Local_s16TempKey);
                }
			}
			else
			{
			    /* If user input number Print this number */
				LCD_vidGoToXY(Clac_u8CursorPosition,0);
				LCD_voidSendChar(Local_s16TempKey);
				Clac_u8CursorPosition++;
                /* If last input was operation  */
				if (Clac_u8FlagNumberOrOperation==0)
				{
				    /* move to new index (To store new number  in the Array)*/
					Calc_u8CounterNumbers++;
					/* move to new index (To store new operations in the Array)*/
					Clac_u8CounterOperations++;
					/* Last input was Number  */
					Clac_u8FlagNumberOrOperation=1;
                    /* Init Operations Counters */
					Calc_u8CounterSeriesOperations=0;
					Clac_u8MulCounter=0;
					Clac_u8DivCounter=0;
					Clac_u8AddCounter=0;
					Clac_u8SubCounter=0;
				}
				/* If user input number then number */
				/* mul first number * 10 */
				Calc_f64Numbers[Calc_u8CounterNumbers]*=10;
				/* then + second number on first number After - 48*/
				/* Local_s16TempNumber is ascii code for number (Local_s16TempNumber-48 to get number */
                /**                                  '3'-48=3                                        **/
				Calc_f64Numbers[Calc_u8CounterNumbers]+=(Local_s16TempKey-48);
				/* User can delete */
				Clac_u8DeletFlag=0;
			}
		}
	}
}
/******************************************************************* Result ******************************************/
void Calc_voidPrintResult()
{
    if (Clac_u8ErrorFlag==0 )
    {
    	u8 Local_u8ZeroCounter=0;
    	u32 Local_u32TempIntNumber;
    	f32 Local_u32TempFloatNumber;
    	LCD_vidGoToXY(0,1);
    	LCD_voidSendString("Ans:");
    	if (Calc_f64Numbers[0]>=0)
    	{
           /* If number is positive  */
           /* Save integer number */
    	   Local_u32TempIntNumber= Calc_f64Numbers[0];
    	   /* save Float  */
           Local_u32TempFloatNumber=Calc_f64Numbers[0]- Local_u32TempIntNumber;
           /* Count number of Zeros before float number*/
    	   while (Local_u32TempFloatNumber<1 && Local_u32TempFloatNumber!=0)
    	   {
    		  Local_u32TempFloatNumber=Local_u32TempFloatNumber*10;
    		  Local_u8ZeroCounter++;
    	   }
    	   /* Print integer number */
           LCD_voidSendNumber(Local_u32TempIntNumber);
           LCD_voidSendString(".");
           /* Print number of Zeros before float number*/
           for(u8 Local_u8Counter=1;Local_u8Counter<Local_u8ZeroCounter;Local_u8Counter++)
           {
               LCD_voidSendNumber(0);
           }
           /* Print float number*/
           LCD_voidSendNumber(Local_u32TempFloatNumber);
    	}
    	else if (Calc_f64Numbers[0]<0)
    	{
    	    /* If number is negative  */
           /* Save integer number */
     	    Local_u32TempIntNumber= (-1)*Calc_f64Numbers[0];
     	    /* Save integer number */
     	    Local_u32TempFloatNumber=(-1)*Calc_f64Numbers[0]-Local_u32TempIntNumber;
     	    /* Count number of Zeros before float number*/
     	    while (Local_u32TempFloatNumber<1 && Local_u32TempFloatNumber!=0)
     	    {
     		   Local_u32TempFloatNumber=Local_u32TempFloatNumber*10;
     		   Local_u8ZeroCounter++;
     	    }
     	    /* Print sign number(-) */
     	    LCD_voidSendString("-");
     	    /* Print integer number */
            LCD_voidSendNumber(Local_u32TempIntNumber);
            LCD_voidSendString(".");
            /* Print number of Zeros before float number*/
            for(u8 Local_u8Counter=1;Local_u8Counter<Local_u8ZeroCounter;Local_u8Counter++)
            {
                LCD_voidSendNumber(0);
            }
            /* Print float number*/
            LCD_voidSendNumber(Local_u32TempFloatNumber);
    	}
    }
    else if(Clac_u8ErrorFlag==1)
    {
    	LCD_vidGoToXY(5,1);
    	/* Print Error if error flag is ==1 */
    	LCD_voidSendString("Error");
    }
}
void Calc_voidCalculateResult (void)
{
	u8 Local_u8CounterOperation=0,Local_u8HeadMulDivOp,Local_u8MulOrDivFlag=0;
    while (Calc_u8CounterNumbers != Local_u8CounterOperation)
    {
        /* Do all Mul and Div operations */
        switch(Calc_u16Operations[Local_u8CounterOperation])
	    {

	       case '*':
	             /* we save all Div and Mul result (without + or - between them  ) in index Local_u8HeadMulDivOp in the array */
	             /**      Calc_f64Numbers[Local_u8HeadMulDivOp]=3*6/2=9  Local_u8HeadMulDivOp is index  3                    **/
	    	     if (Local_u8MulOrDivFlag==0)
	    	     {
	    	         /* Local_u8HeadMulDivOp is index to save mul and div result */
	    		     Local_u8HeadMulDivOp=Local_u8CounterOperation;
	    		     /* a lot of mul and div (without + or - between them  ) */
                     Local_u8MulOrDivFlag=1;
	    	     }
	    	     /* Do operation and save in array  */
	    	     Calc_f64Numbers[Local_u8HeadMulDivOp] = (Calc_f64Numbers[Local_u8HeadMulDivOp] * Calc_f64Numbers[Local_u8CounterOperation+1]);
	    	     /* After do operation Delete parameters of this operation */
	    	     Calc_f64Numbers[Local_u8CounterOperation+1]=0;
                 break;
	       case '/':
	           /* we save all Div and Mul result (without + or - between them  ) in index Local_u8HeadMulDivOp in the array */
               /**      Calc_f64Numbers[Local_u8HeadMulDivOp]=3*6/2=9  Local_u8HeadMulDivOp is index  3                    **/
                if (Local_u8MulOrDivFlag==0)
	    	    {
	    	        /* Local_u8HeadMulDivOp is index to save mul and div result */
	    		    Local_u8HeadMulDivOp=Local_u8CounterOperation;
	    		    /* a lot of mul and div (without + or - between them  ) */
                    Local_u8MulOrDivFlag=1;
	    	    }
	    	    if(Calc_f64Numbers[Local_u8CounterOperation+1]==0)
	    	   {
	    		   Clac_u8ErrorFlag=1;
	    		   break;
	    	   }
	    	   /* Do operation and save in array  */
	    	   Calc_f64Numbers[Local_u8HeadMulDivOp] = (Calc_f64Numbers[Local_u8HeadMulDivOp] / Calc_f64Numbers[Local_u8CounterOperation+1]);
	    	   /* After do operation Delete parameters of this operation */
	    	   Calc_f64Numbers[Local_u8CounterOperation+1]=0;
	           break;
           case '+':
                 /* a lot of mul and div (with + between them  ) */
                 /* new index for Local_u8HeadMulDivOp */
        	     Local_u8MulOrDivFlag=0;
    	         break;
           case '-':
                 /* a lot of mul and div (with  - between them  ) */
                 /* new index for Local_u8HeadMulDivOp */
        	     Local_u8MulOrDivFlag=0;
                 break;
        }
        Local_u8CounterOperation++;
    }
    Local_u8CounterOperation=0;
    /* Do all Add and Sub operations */
    while (Calc_u8CounterNumbers != (Local_u8CounterOperation))
    {
    	if (Calc_u16Operations[Local_u8CounterOperation]=='-')
        {
            Calc_f64Numbers[0] = (Calc_f64Numbers[0] - Calc_f64Numbers[Local_u8CounterOperation+1]);
        }
    	else
        {
            /* Add all element for Array After to check is not sub   */
            Calc_f64Numbers[0] = (Calc_f64Numbers[0] + Calc_f64Numbers[Local_u8CounterOperation+1]);
        }
        Local_u8CounterOperation++;
    }
    /* Print Result */
    Calc_voidPrintResult();
}
/****************************************************** Main *******************************************************/
int  main (void)
{

	LCD_voidInit();
	KPD_voidInit();
	CALC_voidStart();
	while(1)
	{
	    Calc_voidAllInputs();
	    Calc_voidCalculateResult();
	    u8 Local_u8PressedKey;
		while(1)
		{
			Local_u8PressedKey=KPD_u8GetKeyState_HC_543();
			if(Local_u8PressedKey!=KPD_u8_KEY_NOT_PRESSED)
			{
               /* After calculate result if user input C Clear LCD */
			   if ('C' == Local_u8PressedKey )
			   {
				  CALC_voidClearLCD();
				  break;
               }
                /* After calculate result if user input any Key else{ 'C' } used Ans mode  */
			   else if ('C' != Local_u8PressedKey )
			   {
				  CALC_voidUsedAns();
				  break;
			   }
			}
		}
    }
	return 0;
}
