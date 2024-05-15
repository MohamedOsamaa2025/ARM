#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/RCC_interface.h"
#include "../include/GPIO_interface.h"
#include "../include/STK_interface.h"


void main(void)
{
	// Initialize The System Clock
	RCC_voidInit();
	// Enable Clock For GPIOA
	RCC_voidEnablePeripheralClock(RCC_AHB, RCC_AHB_GPIOAEN);

//	// Set PA1 To Be Output pin
//	MGPIO_voidSetPinMode(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT);
//	// Set PA1 To Be Output Push Pull
//	MGPIO_voidSetPinOutputType(GPIO_PORTA, GPIO_PIN1, GPIO_OUTPUT_PP);
//	// Set PA1 To Be Low Speed
//	MGPIO_voidSetPinOutputSpeed(GPIO_PORTA, GPIO_PIN1, GPIO_LOW_SPEED);





	MGPIO_voidSetPortMode(GPIO_PORTA, GPIO_PortOUTPUT);
	MGPIO_voidSetPortOutputType(GPIO_PORTA, GPIO_PortOUTPUT_PP);
	MGPIO_voidSetPortOutputSpeed(GPIO_PORTA, GPIO_PortLOW_SPEED);

	// Initialize SysTick
	MSTK_voidInit();
	while(1)
	{
//		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_HIGH);
//		MSTK_voidSetBusyWait(1000000);
//		MGPIO_voidSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_PIN_LOW);
//		MSTK_voidSetBusyWait(1000000);

// 		LED animation
// 1st animation
//		MGPIO_voidSetPortValue(GPIO_PORTA, 0xffff);
//		MSTK_voidSetBusyWait(1000000);
//		MGPIO_voidSetPortValue(GPIO_PORTA, 0x0000);
//		MSTK_voidSetBusyWait(1000000);
// 2nd animation
//		u8 n=8;
//		for(u8 i=7;i>=0;--i)
//		{
//			for(u8 j=0;j<n;++j)
//			{
//				MSTK_voidSetBusyWait(100000);
//				MGPIO_voidSetPinValue(GPIO_PORTA, j, GPIO_PIN_HIGH);
//				MSTK_voidSetBusyWait(100000);
//				MGPIO_voidSetPinValue(GPIO_PORTA, j, GPIO_PIN_LOW);
//			}
//			MGPIO_voidSetPinValue(GPIO_PORTA, i, GPIO_PIN_HIGH);
//			n--;
//		}
// 3rd animation
		for(u8 j=0;j<8;++j)
		{
			MGPIO_voidSetPinValue(GPIO_PORTA, j, GPIO_PIN_HIGH);
			MSTK_voidSetBusyWait(100000);
			MGPIO_voidSetPinValue(GPIO_PORTA, j, GPIO_PIN_LOW);
			MSTK_voidSetBusyWait(100000);
		}
		for(u8 j=8;j>0;--j)
		{
			MGPIO_voidSetPinValue(GPIO_PORTA, j-1, GPIO_PIN_HIGH);
			MSTK_voidSetBusyWait(100000);
			MGPIO_voidSetPinValue(GPIO_PORTA, j-1, GPIO_PIN_LOW);
			MSTK_voidSetBusyWait(100000);
		}
// 4th animation
//		for(u8 j=1,i=0;j<5;++j,++i)
//		{
//
//			MGPIO_voidSetPinValue(GPIO_PORTA, (8/2)-j, GPIO_PIN_HIGH);
//			MGPIO_voidSetPinValue(GPIO_PORTA,(8/2)+i , GPIO_PIN_HIGH);
//			MSTK_voidSetBusyWait(100000);
//		}
//// 5th animation
//		for(u8 j=4,i=3;j>1;--j,--i)
//		{
//
//			MGPIO_voidSetPinValue(GPIO_PORTA, (8/2)-j, GPIO_PIN_LOW);
//			MGPIO_voidSetPinValue(GPIO_PORTA,(8/2)+i , GPIO_PIN_LOW);
//			MSTK_voidSetBusyWait(100000);
//		}



}
}
