/*
 * CrossCoreIPC.c
 *
 * Description: Functions to perform inter-processor communication.
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#include <stdio.h>
#include <stdlib.h>


/**
* Assume that the device has Inter-Processor Communication (IPC) channels as an underlying hardware layer
* since it is a dual-core system.
**/

void CPU1_IPC_Init(uint8_t ChannelNo)
{
	//The configuration here is hardware-dependent.
}

uint8_t CPU1_Acquire_IPC_Lock(uint8_t ChannelNo)
{
	//This is hardware-dependent part.

	return 1;//Lock successful
}

void CPU1_Notify_IPC_Lock(uint8_t ChannelNo)
{
	//This is hardware-dependent part.
}

uint8_t CPU1_Release_IPC_Lock(uint8_t ChannelNo)
{
	//This is hardware-dependent part.

	return 1;//Released lock successful
}

uint8_t CPU1_Check_IPC_Notification(uint8_t ChannelNo)
{
	uint8_t NotiStatus = 0;

	//Dummy check since there is no info about actual IPC.
	//Actual implementation needs to be added with real system.
	if(1)
	{
		NotiStatus = 1;
	}else{
		NotiStatus = 0;
	}

	return NotiStatus;
}


uint8_t CPU1_Check_IPC_Release(uint8_t ChannelNo)
{
	uint8_t ReleaseStatus = 0;

	//Dummy check on corresponding channel since there is no info about actual IPC.
	//Actual implementation needs to be added with real system.
	if(1 /* if release status is set in the HW register. */)
	{
		ReleaseStatus = 1;
	}else{
		ReleaseStatus = 0;
	}

	return ReleaseStatus;
}

/****************************************/
uint8_t Channel1_Noti = 0;
uint8_t Channel1_Ack = 0;

//Dummy implementation of ISR functions
void ISR_from_IPC_Channel0(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU1_Check_IPC_Notification(0);//Acknowledge
	}

	if(1 /* if release status is set in the HW register. */)
	{
		CPU1_Check_IPC_Release(0);//Acknowledge
	}

}

void ISR_from_IPC_Channel1(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		Channel1_Noti = CPU1_Check_IPC_Notification(1);//Acknowledge
	}

	if(1 /* if release status is set in the HW register. */)
	{
		Channel1_Ack = CPU1_Check_IPC_Release(1);//Acknowledge
	}

}

void ISR_from_IPC_Channel2(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU1_Check_IPC_Notification(2);//Acknowledge
	}

	if(1 /* if release status is set in the HW register. */)
	{
		CPU1_Check_IPC_Release(2);//Acknowledge
	}

}

void ISR_from_IPC_Channel3(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU1_Check_IPC_Notification(3);//Acknowledge
	}

	if(1 /* if release status is set in the HW register. */)
	{
		CPU1_Check_IPC_Release(3);//Acknowledge
	}

}
/*****************************************/
