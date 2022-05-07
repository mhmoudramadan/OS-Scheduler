/*
 * ROTS_Interface.h
 *
 *  Created on: Mar 18, 2022
 *      Author: Dell
 */

#ifndef RTOS_STACK_RTOS_INTERFACE_H_
#define RTOS_STACK_RTOS_INTERFACE_H_

#define TASK_RESUME   1
#define TASK_SUSPEND  0

/*RTOS Create Task*/
void RTOS_VidTaskCreate(void(*PtrToFun)(void),uint32 Periodicity,uint8 Priority,uint32 FirstDealy);
/*RTOS Start Scheduler*/
void RTOS_VidStartScheduler(void);

void RTOS_VidTask_Suspend(uint8 copy_uint8Priority);
void RTOS_VidTask_Resume(uint8 copy_uint8Priority);
void RTOS_VidTask_Delete(uint8 copy_uint8Priority);

#endif /* RTOS_STACK_RTOS_INTERFACE_H_ */
