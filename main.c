/*
 * main.c
 *
 *  Created on: Mar 18, 2022
 *      Author: Dell
 */
#include"LIB/LSTD_TYPES.h"
#include"MCAL/MDIO/MDIO_Interface.h"
#include"HAL/HLED/HLED_Interface.h"
#include "RTOS_STACK/RTOS_Interface.h"


LED_T led0={MDIO_PORTC,PIN2,ACTIVE_HIGH};
LED_T led1={MDIO_PORTC,PIN7,ACTIVE_HIGH};
LED_T led2={MDIO_PORTD,PIN3,ACTIVE_HIGH};

void APP_vidLed1(void);
void APP_vidLed2(void);
void APP_vidLed3(void);
int main(void)
{
	HLED_Errorstate_Led_Init(&led0);
	HLED_Errorstate_Led_Init(&led1);
	HLED_Errorstate_Led_Init(&led2);

	RTOS_VidTaskCreate(APP_vidLed1,1000,0,0);
	RTOS_VidTaskCreate(APP_vidLed2,2000,1,1000);
	RTOS_VidTaskCreate(APP_vidLed3,3000,2,2000);
	RTOS_VidStartScheduler();
	while(1)
	{

	}
	return 0;
}
void APP_vidLed1(void)
{
	static uint8 flag=0;
	if(flag==0)
	{
	HLED_Errorstate_Led_On(&led0);
	flag=1;
	}
	else
	{
		HLED_Errorstate_Led_Off(&led0);
		flag=0;
	}
}
void APP_vidLed2(void)
{
	static uint8 flag=0;
	if(flag==0)
	{
	HLED_Errorstate_Led_On(&led1);
	flag=1;
	}
	else
	{
		HLED_Errorstate_Led_Off(&led1);
		flag=0;
	}
}
void APP_vidLed3(void)
{
	static uint8 flag=0;
	if(flag==0)
	{
	HLED_Errorstate_Led_On(&led2);
	flag=1;
	}
	else
	{
		HLED_Errorstate_Led_Off(&led2);
		flag=0;
	}
}
