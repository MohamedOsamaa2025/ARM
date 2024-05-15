/*********************************************
 * Author:				Abdullah M. Abdullah
 * Creation Data:		22 Mar, 2024
 * Version:				v1.0
 * Compiler:			GNU ARM-GCC
 * Controller:			STM32F401CCU6
 * Layer:				HAL
 ********************************************/
/*********************************************
 * Version	  Date				  Author				  Description
 * v1.0		  22 Mar, 2024	Abdullah M. Abdullah		  Initial Creation
*********************************************/
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/GPIO_interface.h"
#include "../include/STK_interface.h"


#include "../include/LEDMAT_interface.h"
#include "../include/LEDMAT_private.h"
#include "../include/LEDMAT_config.h"



void HLEDMAT_voidInit(void)
{
    for(u8 i=0;i<8;++i)
    {

        /*Set Columns Pins To Be Output*/
        MGPIO_voidSetPinMode(HLEDMAT_COL_PORT,i, GPIO_OUTPUT);
        /*Set Columns Pins To Be Output PP*/
        MGPIO_voidSetPinOutputType(HLEDMAT_COL_PORT,i, GPIO_OUTPUT_PP);
        /*Set Columns Pin To Be Output Low Speed*/
        MGPIO_voidSetPinOutputSpeed(HLEDMAT_COL_PORT,i, GPIO_LOW_SPEED);
        /*Set Rows Pins To Be Output*/
        MGPIO_voidSetPinMode(HLEDMAT_ROW_PORT,i, GPIO_OUTPUT);
        /*Set Rows Pins To Be Output PP*/
        MGPIO_voidSetPinOutputType(HLEDMAT_ROW_PORT,i, GPIO_OUTPUT_PP);
        /*Set Rows Pin To Be Output Low Speed*/
        MGPIO_voidSetPinOutputSpeed(HLEDMAT_ROW_PORT,i, GPIO_LOW_SPEED);
    }
}

void HLED_voidDisplay(u8 * Copy_pu8Data)
{
    for(u8 i=0;i<8;++i)
    {
        /*Disable All Columns*/
        voidDisableAllColumns();
        /*Set Rows Value*/
        voidSetRowsValue(Copy_pu8Data[i]);
        /*Activate Column 0*/
        MGPIO_voidSetPinValue(HLEDMAT_COL_PORT,i, GPIO_PIN_LOW);
        /*Delay for 2.5msec*/
        MSTK_voidSetBusyWait(2500);
    }
}

static void voidDisableAllColumns(void)
{
    for(u8 i=0;i<8;++i)
    {
        MGPIO_voidSetPinValue(HLEDMAT_COL_PORT,i, GPIO_PIN_HIGH);
    }    

}

static void voidSetRowsValue(u8 Copy_u8Value)
{
    u8 Local_u8Bit;
    /*Set Rows Value*/
    for(u8 i=0;i<8;++i)
    {
        Local_u8Bit = GET_BIT(Copy_u8Value, i);
        MGPIO_voidSetPinValue(HLEDMAT_ROW_PORT,i, Local_u8Bit);
    }
}