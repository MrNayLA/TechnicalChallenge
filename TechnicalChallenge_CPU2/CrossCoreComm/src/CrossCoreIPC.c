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

#include "CrossCoreIPC.h"

/**
* Assume that the device has Inter-Processor Communication (IPC) channels as an underlying hardware layer
* since it is a dual-core system.
**/

void CPU2_IPC_Init(uint16_t ChannelNo)
{
	//The configuration here is hardware-dependent.
}

uint16_t CPU2_Acquire_IPC_Lock(uint16_t ChannelNo)
{
	//This is hardware-dependent part.
	return 1;//Lock successful
}

void CPU2_Notify_IPC(uint16_t ChannelNo)
{
	//This is hardware-dependent part.
}

void CPU2_SendMessage_IPC(uint16_t ChannelNo,char *Addr, uint32_t DataSize)
{
	//Pass starting address of the shared memory and data length to the register of the IPC channel used.

	IPC_Msg_t IpcMsg = {0};

	IpcMsg.ptrMessage = Addr;/* Starting address of data to be sent via IPC */
	IpcMsg.MsgInfo.bit_view.MessageSize = DataSize;/* data size */
	IpcMsg.MsgInfo.bit_view.Identifier = enSendNotify;/* Identifier */

	/* Write into the IPC registers. This should be implemented only in real system. */
	//*IPC_DataReg1 = (uint32_t)IpcMsg.ptrMessage;
	//*IPC_DataReg2 = (((uint32_t)IpcMsg.MsgInfo.bit_view.Identifier << 16) || ((uint32_t)IpcMsg.MsgInfo.bit_view.MessageSize & 0xffff));

}


void CPU2_SendAck(uint16_t ChannelNo)
{
	IPC_Msg_t IpcMsg = {0};

	IpcMsg.ptrMessage = 0;/* Starting address of data to be sent via IPC */
	IpcMsg.MsgInfo.bit_view.MessageSize = 0;/* data size */
	IpcMsg.MsgInfo.bit_view.Identifier = enSendAck;/* Identifier */

	/* Write into the IPC registers. This should be implemented only in real system. */
	//*IPC_DataReg1 = (uint32_t)IpcMsg.ptrMessage;
	//*IPC_DataReg2 = (((uint32_t)IpcMsg.MsgInfo.bit_view.Identifier << 16) | ((uint32_t)IpcMsg.MsgInfo.bit_view.MessageSize & 0xffff));

}

uint16_t CPU2_Release_IPC_Lock(uint16_t ChannelNo)
{
	//This is hardware-dependent part.

	return 1;//Released lock successful
}

uint16_t CPU2_Check_IPC_Notification(uint16_t ChannelNo)
{
	uint16_t NotiStatus = 0;

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


uint16_t CPU2_Check_IPC_Release(uint8_t ChannelNo)
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
uint16_t Channel1_Noti = 0;
uint16_t Channel1_Ack = 0;

//Dummy implementation of ISR functions
void ISR_from_IPC_Channel0(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU2_Check_IPC_Notification(0);//Acknowledge
	}

	if(1 /* if release status is set in the HW register. */)
	{
		CPU2_Check_IPC_Release(0);//Acknowledge
	}

}

void ISR_from_IPC_Channel1(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		Channel1_Noti = CPU2_Check_IPC_Notification(1);//Acknowledge
	}

	if(1 /* if release status is set in the HW register. */)
	{
		Channel1_Ack = CPU2_Check_IPC_Release(1);//Acknowledge
	}

}

void ISR_from_IPC_Channel2(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU2_Check_IPC_Notification(2);//Acknowledge
	}

	if(1 /* if release status is set in the HW register. */)
	{
		CPU2_Check_IPC_Release(2);//Acknowledge
	}

}

void ISR_from_IPC_Channel3(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU2_Check_IPC_Notification(3);//Acknowledge
	}

	if(1 /* if release status is set in the HW register. */)
	{
		CPU2_Check_IPC_Release(3);//Acknowledge
	}

}
/*****************************************/
