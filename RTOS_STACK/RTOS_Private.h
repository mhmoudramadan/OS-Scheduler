/*
 * RTOS_Private.h
 *
 *  Created on: Mar 18, 2022
 *      Author: Dell
 */

#ifndef RTOS_STACK_RTOS_PRIVATE_H_
#define RTOS_STACK_RTOS_PRIVATE_H_


typedef struct
	{
		void(*TaskFun)(void);
		uint32 Periodicity;
		uint8 TaskState;
		uint32 FirstDelay;

	}Task_t;

/*RTOS Scheduler*/
void RTOS_VidScheduler(void);
void RTOS_VidScheduler11(void);

#endif /* RTOS_STACK_RTOS_PRIVATE_H_ */
