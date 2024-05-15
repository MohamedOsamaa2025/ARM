/*
 * main.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Lenovo
 */



#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"

#include "../include/RCC_interface.h"
#include "../include/GPIO_interface.h"
#include "../include/STK_interface.h"
#include "../include/LEDMAT_interface.h"


//u8 arr[8]={255,2,4,8,8,4,2,255};


u8 arr1[3][8]={{132, 75, 127, 75, 132, 64, 0, 0},
			   {132, 75, 127, 75, 132, 32, 0, 0},
			   {132, 75, 127, 75, 132, 16, 0, 0}};

u8 arr2[2][8]={{0, 172, 126, 172, 0, 0, 0, 0},
			   {0, 172, 125, 172, 0, 0, 0, 0}};

u8 arr3[6][8]={{144, 75, 127, 75, 144, 64, 0, 0},
			   {144, 75, 127, 75, 144, 0, 32, 0},
			   {144, 75, 127, 75, 144, 0, 0, 16},
			   {144, 75, 127, 75, 144, 0, 8, 0},
			   {144, 75, 127, 75, 144, 4, 0, 0},
			   {144, 75, 127, 75, 146, 0, 0, 0}};

void main(void)
{
	RCC_voidInit();
	RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOAEN);
	RCC_voidEnablePeripheralClock(RCC_AHB,RCC_AHB_GPIOBEN);

	MSTK_voidInit();

	HLEDMAT_voidInit();

	while(1)
	{
//				z3bola skills
//	1st skill
	    for(u8 i=0;i<8;++i)
		HLED_voidDisplay(&arr1[0]);
	    for(u8 i=0;i<8;++i)
	    HLED_voidDisplay(&arr1[1]);
	    for(u8 i=0;i<8;++i)
		HLED_voidDisplay(&arr1[2]);
	    for(u8 i=0;i<8;++i)
		HLED_voidDisplay(&arr1[1]);
	    for(u8 i=0;i<8;++i)
		HLED_voidDisplay(&arr1[0]);
        MSTK_voidSetBusyWait(150000);
//	2nd skill
	    for(u8 i=0;i<10;++i)
		HLED_voidDisplay(&arr2[0]);
	    for(u8 i=0;i<10;++i)
		HLED_voidDisplay(&arr2[1]);
	    for(u8 i=0;i<10;++i)
		HLED_voidDisplay(&arr2[0]);
        MSTK_voidSetBusyWait(150000);
//	3rd skill
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[0]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[1]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[2]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[3]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[4]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[5]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[4]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[3]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[2]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[1]);
	for(u8 i=0;i<7;++i)
	HLED_voidDisplay(&arr3[0]);
		MSTK_voidSetBusyWait(150000);


		//print 1st letter of your name
//		HLED_voidDisplay(arr);
	}
}

