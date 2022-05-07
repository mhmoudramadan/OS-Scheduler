/*
 * RTOS_Program.c
 *
 *  Created on: Mar 18, 2022
 *      Author: Dell
 */
#include"../LIB/LSTD_TYPES.h"
#include"../MCAL/MTIMER0/MTIMER0_Config.h"
#include"../MCAL/MTIMER0/MTIMER0_Interface.h"
#include"../MCAL/MGIE/MGIE_Interface.h"

#include "RTOS_Config.h"
#include "RTOS_Interface.h"
#include "RTOS_Private.h"

Task_t TCBs[MAX_TASKS]={{NULL}};

/*RTOS Create Task*/
void RTOS_VidTaskCreate(void(*PtrToFun)(void),uint32 Periodicity,uint8 Priority, uint32 FirstDealy)
{

	if(TCBs[Priority].TaskFun==NULL)
	{
		TCBs[Priority].TaskFun=PtrToFun;
		TCBs[Priority].Periodicity=Periodicity;
		TCBs[Priority].TaskState=TASK_RESUME;
		TCBs[Priority].FirstDelay=FirstDealy;
    }
	else
	{
		/*Do nothing*/
	}
}
	/*RTOS Start Scheduler*/
void RTOS_VidStartScheduler(void)
{
	uint8 CTCValue;
	uint32 Ticktime;

	/*Calculations of CTC Value */
	Ticktime=(TIMER_PRESCALER*1000000)*1000/FCPU;
	CTCValue=(SYSTICK_ms*1000000)/Ticktime;

	/*load algorithm*/
	MTIMER0_VidTimerCTC_SetCallBack(RTOS_VidScheduler11);

	/*initialize timer0 at CTC Mode */
	MTIMER0_VidSetCTCRegister(CTCValue);
	MTIMER0_VidInit();
	MGIE_Enable();
}

/*RTOS Scheduler*/
void RTOS_VidScheduler(void)
{
	uint8 i;
	static uint32 SysCount=0;
	SysCount++;

	for(i=0;i<MAX_TASKS;i++)
	{
		if(TCBs[i].TaskState==TASK_RESUME  &&  TCBs[i].TaskFun!=NULL )
			{
				if(SysCount % TCBs[i].Periodicity==0)
				{
					TCBs[i].TaskFun();
				}
				else
				{
					/*Do nothing*/
				}
			}
		else
			{
				/*Do nothing*/
			}
	}
}

void RTOS_VidTask_Suspend(uint8 copy_uint8Priority)
{
	TCBs[copy_uint8Priority].TaskState=TASK_SUSPEND;
}

void RTOS_VidTask_Resume(uint8 copy_uint8Priority)
{
	TCBs[copy_uint8Priority].TaskState=TASK_RESUME;
}

void RTOS_VidTask_Delete(uint8 copy_uint8Priority)
{
	TCBs[copy_uint8Priority].TaskFun=NULL;
}


void RTOS_VidScheduler11(void)
{

	uint8 i;

	for(i=0;i<MAX_TASKS;i++)
	{
		if(TCBs[i].TaskState==TASK_RESUME  &&  TCBs[i].TaskFun!=NULL )
		{
	    	 if(TCBs[i].FirstDelay==0)
	    	 	 {
	    		 	 TCBs[i].TaskFun();
	    		 	 TCBs[i].FirstDelay=TCBs[i].Periodicity-1;
	    	 	 }
	    	 	 else
	    	 	  {
	    	 		 TCBs[i].FirstDelay--;
	    	 	  }
		}
		else
		{
			/*Do nothing*/
		}
	}
}
