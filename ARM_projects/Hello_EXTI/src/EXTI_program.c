/*********************************************
 * Author:				Abdullah M. Abdullah
 * Creation Data:		29 Mar, 2024
 * Version:				v1.0
 * Compiler:			GNU ARM-GCC
 * Controller:			STM32F401CCU6
 * Layer:				MCAL
 ********************************************/
/*********************************************
 * Version	  Date				  Author				  Description
 * v1.0		  29 Mar, 2024	Abdullah M. Abdullah		  Initial Creation
*********************************************/
#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/EXTI_interface.h"
#include "../include/EXTI_private.h"
#include "../include/EXTI_config.h"

//#include "../include/NVIC_interface.h"

// static void (*EXTI0_pNotificationFunction)(void) = NULLPTR;
// static void (*EXTI1_pNotificationFunction)(void) = NULLPTR;

// Array Of Pointers to Function
static void (*EXTI_pNotificationFunction[16])(void) = {NULLPTR};


// Task
void MEXTI_voidInit(void)
{
    #if( EXTI0_port==0)
        SYSCFG_EXTICR1 &=~(15 << 0);
        SYSCFG_EXTICR1 |=(EXTI0_port << 0);
    #elif(EXTI0_port==1)
        SYSCFG_EXTICR1 &=~(15<<0);
        SYSCFG_EXTICR1 |=(EXTI0_port << 0);    
    #elif(EXTI0_port==2)
        SYSCFG_EXTICR1 &=~(15<<0);
        SYSCFG_EXTICR1 |=(EXTI0_port << 0);    
    #else   
    #endif

    #if( EXTI1_port==0)
        SYSCFG_EXTICR1 &=~(15 << 4);
        SYSCFG_EXTICR1 |=(EXTI1_port << 4);
    #elif(EXTI1_port==1)
        SYSCFG_EXTICR1 &=~(15<<4);
        SYSCFG_EXTICR1 |=(EXTI1_port << 4);    
    #elif(EXTI1_port==2)
        SYSCFG_EXTICR1 &=~(15<<4);
        SYSCFG_EXTICR1 |=(EXTI1_port << 4);    
    #else
    #endif

    #if( EXTI2_port==0)
        SYSCFG_EXTICR1 &=~(15 << 8);
        SYSCFG_EXTICR1 |=(EXTI2_port << 8);
    #elif(EXTI2_port==1)
        SYSCFG_EXTICR1 &=~(15<<8);
        SYSCFG_EXTICR1 |=(EXTI2_port << 8);    
    #elif(EXTI2_port==2)
        SYSCFG_EXTICR1 &=~(15<<8);
        SYSCFG_EXTICR1 |=(EXTI2_port << 8);    
    #else
    #endif

    #if( EXTI3_port==0)
        SYSCFG_EXTICR1 &=~(15 << 12);
        SYSCFG_EXTICR1 |=(EXTI3_port << 12);
    #elif(EXTI3_port==1)
        SYSCFG_EXTICR1 &=~(15<<12);
        SYSCFG_EXTICR1 |=(EXTI3_port << 12);    
    #elif(EXTI3_port==2)
        SYSCFG_EXTICR1 &=~(15<<12);
        SYSCFG_EXTICR1 |=(EXTI3_port << 12);    
    #else
    #endif


    #if(EXTI_enable_0==1)
        SET_BIT(EXTI->IMR, 0);
    #endif    
    #if(SenseSignal_0==0)
        CLR_BIT(EXTI->FTSR, 0);
        SET_BIT(EXTI->RTSR, 0);
    #elif(SenseSignal==1)
        CLR_BIT(EXTI->RTSR, 0);
        SET_BIT(EXTI->FTSR, 0);
    #else
        SET_BIT(EXTI->RTSR, 0);
        SET_BIT(EXTI->FTSR, 0);          
    #endif   

    #if(EXTI_enable_1==1)
        SET_BIT(EXTI->IMR, 1);
    #endif    
    #if(SenseSignal_1==0)
        CLR_BIT(EXTI->FTSR, 1);
        SET_BIT(EXTI->RTSR, 1);
    #elif(SenseSignal_1==1)
        CLR_BIT(EXTI->RTSR, 1);
        SET_BIT(EXTI->FTSR, 1);
    #else
        SET_BIT(EXTI->RTSR, 1);
        SET_BIT(EXTI->FTSR, 1);          
    #endif 

    #if(EXTI_enable_2==1)
        SET_BIT(EXTI->IMR, 2);
    #endif    
    #if(SenseSignal_2==0)
        CLR_BIT(EXTI->FTSR, 2);
        SET_BIT(EXTI->RTSR, 2);
    #elif(SenseSignal_2==1)
        CLR_BIT(EXTI->RTSR, 2);
        SET_BIT(EXTI->FTSR, 2);
    #else
        SET_BIT(EXTI->RTSR, 2);
        SET_BIT(EXTI->FTSR, 2);          
    #endif   

    #if(EXTI_enable_3==1)
        SET_BIT(EXTI->IMR, 3);
    #endif    
    #if(SenseSignal_3==0)
        CLR_BIT(EXTI->FTSR, 3);
        SET_BIT(EXTI->RTSR, 3);
    #elif(SenseSignal_3==1)
        CLR_BIT(EXTI->RTSR, 3);
        SET_BIT(EXTI->FTSR, 3);
    #else
        SET_BIT(EXTI->RTSR, 3);
        SET_BIT(EXTI->FTSR, 3);          
    #endif   

}

void MEXTI_voidEnableInterrupt(MEXTI_INTERRUPT_LINE_t Copy_tInterrupLine)
{
    SET_BIT(EXTI->IMR, Copy_tInterrupLine);
}

void MEXTI_voidDisableInterrupt(MEXTI_INTERRUPT_LINE_t Copy_tInterrupLine)
{
    CLR_BIT(EXTI->IMR, Copy_tInterrupLine);
}

void MEXTI_voidChangePin(MEXTI_INTERRUPT_LINE_t Copy_tInterrupLine,u8 Copy_u8Port)
{    
    switch(Copy_tInterrupLine)
    {
        case MEXTI_EXTI0:
            SYSCFG_EXTICR1 &=~(15 << 0);
            SYSCFG_EXTICR1 |=(Copy_u8Port << 0);        
        break;
        case MEXTI_EXTI1:
            SYSCFG_EXTICR1 &=~(15 << 4);
            SYSCFG_EXTICR1 |=(Copy_u8Port << 4);
        break;
        case MEXTI_EXTI2:
            SYSCFG_EXTICR1 &=~(15 << 8);
            SYSCFG_EXTICR1 |=(Copy_u8Port << 8);
        break;
        case MEXTI_EXTI3:
            SYSCFG_EXTICR1 &=~(15 << 12);
            SYSCFG_EXTICR1 |=(Copy_u8Port << 12);
        break;
        
    }
}

void MEXTI_voidChangeSenseMode(MEXTI_INTERRUPT_LINE_t Copy_tInterrupLine, MEXTI_INTERRUPT_SENSE_SIGNAL_t Copy_tSenseSignal)
{
    switch(Copy_tSenseSignal)
    {
        case MEXTI_RISING:
            CLR_BIT(EXTI->FTSR, Copy_tInterrupLine);
            SET_BIT(EXTI->RTSR, Copy_tInterrupLine);
        break;

        case MEXTI_FALLING:
            CLR_BIT(EXTI->RTSR, Copy_tInterrupLine);
            SET_BIT(EXTI->FTSR, Copy_tInterrupLine);
        break;

        case MEXTI_ONCHANGE:
            SET_BIT(EXTI->RTSR, Copy_tInterrupLine);
            SET_BIT(EXTI->FTSR, Copy_tInterrupLine);
        break;

        default:
        break;
    }
}

void MEXTI_voidSetCallBack(MEXTI_INTERRUPT_LINE_t Copy_tInterrupLine, void (*pCallBackFunction)(void))
{
    switch(Copy_tInterrupLine)
    {
        case MEXTI_EXTI0:
            // EXTI0_pNotificationFunction = pCallBackFunction;
            EXTI_pNotificationFunction[Copy_tInterrupLine] = pCallBackFunction;
        break;
        case MEXTI_EXTI1:
            // EXTI1_pNotificationFunction = pCallBackFunction;
            EXTI_pNotificationFunction[Copy_tInterrupLine] = pCallBackFunction;

        break;
    }
}

// ISR For EXTI0
void EXTI0_IRQHandler(void)
{
//	MNVIC_voidClearPendingFlag(6);
//  MNVIC_u8GetActiveFlag(6);
	SET_BIT(EXTI->PR, 0);

    // if(EXTI0_pNotificationFunction != NULLPTR)
    if(EXTI_pNotificationFunction[0] != NULLPTR)
    {
        // EXTI0_pNotificationFunction();
        EXTI_pNotificationFunction[0]();
    }
    else
    {
        // Do Nothing
    }
}

// ISR For EXTI1
void EXTI1_IRQHandler(void)
{
	//	MNVIC_voidClearPendingFlag(7);
	//  MNVIC_u8GetActiveFlag(7);
	SET_BIT(EXTI->PR, 1);
    if(EXTI_pNotificationFunction[1] != NULLPTR)
    {
        EXTI_pNotificationFunction[1]();
    }
    else
    {
        // Do Nothing
    }
}


