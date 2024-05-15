#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/RCC_interface.h"
#include "../include/GPIO_interface.h"
#include "../include/NVIC_interface.h"
#include "../include/STK_interface.h"
#include "../include/EXTI_interface.h"


#define NO_START	0
#define START		1

void GetFrame(void);
void TakeAction(void);
void APP_voidPlay(void);

u8 u8ButtonData = 0;
u8 APP_u8StartBitFlag = NO_START;
u8 u8EdgeCounter = 0;
u32 u32ReceivedFrame[100];

void main(void)
{
	/*Initialize The System Clock*/
	RCC_voidInit();
	/*Enable GPIOA Peripheral Clock*/
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);

	/*Set RGB LED Pins, PA1, PA2, and PA3*/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT);
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN3, GPIO_OUTPUT);

	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN1, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN2, GPIO_LOW_SPEED);
	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN3, GPIO_LOW_SPEED);

	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN2, GPIO_OUTPUT_PP);
	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN3, GPIO_OUTPUT_PP);

	/*Set PA0 To Be Input Float*/
	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN0, GPIO_INPUT);

	/*Initialize The SysTick*/
	MSTK_voidInit();

	/*Initialize The NVIC*/
	MNVIC_voidInit();

	/*Setup EXTI0 To Sense The Falling Edge*/
	MEXTI_voidChangeSenseMode(MEXTI_EXTI0, MEXTI_FALLING);
	/*Set The Callback function for EXTI0*/
	MEXTI_voidSetCallBack(MEXTI_EXTI0, &GetFrame);
	/*Enable EXTI0*/
	MEXTI_voidEnableInterrupt(MEXTI_EXTI0);

	/*NVIC Enable Interrupt For EXTI0*/
	MNVIC_voidPeripheralInterruptControl(6, MNVIC_INT_ENABLE);

	while(1)
	{
		;
	}
}

void GetFrame(void)
{
	if(APP_u8StartBitFlag == NO_START)
	{
		MSTK_voidSetPreloadValue(100000);
		MSTK_voidSetSingleInterval(&TakeAction);
		APP_u8StartBitFlag = START;
	}
	else
	{
		u32ReceivedFrame[u8EdgeCounter] = MSTK_u32GetElapsedTime();
		MSTK_voidResetTimer();
		MSTK_voidSetPreloadValue(100000);
		u8EdgeCounter++;
	}
}



void TakeAction(void)
{
	u8 Local_u8LoopCounter = 0;
	for(Local_u8LoopCounter = 0; Local_u8LoopCounter < 8; Local_u8LoopCounter++)
	{
		if(		(u32ReceivedFrame[17+Local_u8LoopCounter] >= 1000) &&
				(u32ReceivedFrame[17+Local_u8LoopCounter] <= 1500))
		{
			CLR_BIT(u8ButtonData, Local_u8LoopCounter);
		}
		else
		{
			SET_BIT(u8ButtonData, Local_u8LoopCounter);
		}
	}
	u8EdgeCounter = 0;
	APP_u8StartBitFlag = NO_START;
	MSTK_voidSTKEnable();
	APP_voidPlay();
}


/* nippon remote control
 * Power Button -> 128
 * 1 Button -> 144
 * 2 Button -> 136
 * 3 Button -> 132
 * 4 Button -> 131
 * 5 Button -> 130
 * 6 Button -> 129
 * 7 Button -> 135
 * 8 Button -> 134
 *
 */

void APP_voidPlay(void)
{
	static u8 Local_u8B1State=0;
	static u8 Local_u8B2State=0;
	static u8 Local_u8B3State=0;
	static u8 Local_u8B4State=0;
	static u8 Local_u8B5State=0;
	static u8 Local_u8B6State=0;
	static u8 Local_u8PowerBState=0;
	switch(u8ButtonData)
	{
	case 144:
		Local_u8B1State ^=1;
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, Local_u8B1State); // RED LED Turn On
		break;
	case 136:
		Local_u8B2State ^=1;
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, Local_u8B2State); // GREEN LED Turn On
		break;
	case 132:
		Local_u8B3State ^=1;
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, Local_u8B3State); // BLUE LED Turn On
		break;
	case 131:
		Local_u8B4State ^=1;
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, Local_u8B4State); // BLUE LED Turn On
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, Local_u8B4State); // BLUE LED Turn On
		break;
	case 130:
		Local_u8B5State ^=1;
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, Local_u8B5State); // BLUE LED Turn On
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, Local_u8B5State); // BLUE LED Turn On
		break;
	case 129:
		Local_u8B6State ^=1;
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, Local_u8B6State); // BLUE LED Turn On
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, Local_u8B6State); // BLUE LED Turn On
		break;
	case 128:
		Local_u8PowerBState ^=1;
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, Local_u8PowerBState); // RED LED Turn Off
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN2, Local_u8PowerBState); // GREEN LED Turn Off
		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN3, Local_u8PowerBState); // BLUE LED Turn Off
		break;
	default:
		break;
	}
}

/* Power Button -> 69
 * Mute Button -> 71
 * 1 Button -> 12
 * 2 Button -> 24
 * 3 Button -> 94
 * */



