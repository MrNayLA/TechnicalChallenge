/*
 * CrossCoreIPC.c
 *
 * Description: Functions to perform inter-processor communication.
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#include <stdlib.h>
#include "CrossCoreConfig.h"
#include "CPU2_CrossCoreIPC.h"

uint16_t CPU2_TestLockStatus = 1;//Used for mock test Only
IPC_Msg_t CPU2_IpcMessage = {0};//IPC Msg buffer

/**
* Hard-dependancy:
* Assume that the device has Inter-Processor Communication (IPC) channels as an underlying hardware layer
* since it is a dual-core system.
**/

void CPU2_IPC_Init(uint16_t ChannelNo)
{
	//The configuration here is hardware-dependant.
}

uint16_t CPU2_Acquire_IPC_Lock(uint16_t ChannelNo)
{
	//This is hardware-dependent part.

	uint16_t LockStatus = 0;

	LockStatus = CPU2_TestLockStatus;//Used for mock test Only

	return LockStatus;

	//return 1;//Lock successful
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
	IpcMsg.MsgInfo.bit_view.Identifier = enSendAck;/* Just send Identifier to signal acknowledgement. */

	/* Write into the IPC registers.This should be implemented only in real system. */
	//*IPC_DataReg1 = (uint32_t)IpcMsg.ptrMessage;
	//*IPC_DataReg2 = (((uint32_t)IpcMsg.MsgInfo.bit_view.Identifier << 16) || ((uint32_t)IpcMsg.MsgInfo.bit_view.MessageSize & 0xffff));

}

/* Read data from IPC's data registers. */
void CPU2_Read_IPC_RegData(uint16_t ChannelNo, IPC_Msg_t* ptrIpcMsg)
{
	/* This register read can only be performed in actual system. */
	//ptrIpcMsg->ptrMessage = (const char *)(*IPC_DataReg1);
	//ptrIpcMsg->MsgInfo.bit_view.MessageSize = (*IPC_DataReg2 & 0xffff);
	//ptrIpcMsg->MsgInfo.bit_view.Identifier = ((*IPC_DataReg2 >> 16) & 0xffff);

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
	uint16_t ReleaseStatus = 0;

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
uint16_t u16Channel1_Noti = 0;
uint16_t u16Channel1_Ack = 0;

//Dummy implementation of ISR functions
void CPU2_ISR_from_IPC_Channel0(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU2_Check_IPC_Notification(0);//Acknowledge

		CPU2_Read_IPC_RegData(0, &CPU2_IpcMessage);//Do outside?
	}

	if(1 /* if release status is set in the HW register. */)
	{
		u16Channel1_Ack = CPU2_Check_IPC_Release(0);//Acknowledge
	}

}



void CPU2_ISR_from_IPC_Channel1(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		u16Channel1_Noti = CPU2_Check_IPC_Notification(1);//Notify

		CPU2_Read_IPC_RegData(1, &CPU2_IpcMessage);
	}

	if(1 /* if release status is set in the HW register. */)
	{
		u16Channel1_Ack = CPU2_Check_IPC_Release(1);//Acknowledge
	}

}

void CPU2_ISR_from_IPC_Channel2(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU2_Check_IPC_Notification(2);//Acknowledge

		CPU2_Read_IPC_RegData(2, &CPU2_IpcMessage);
	}

	if(1 /* if release status is set in the HW register. */)
	{
		u16Channel1_Ack = CPU2_Check_IPC_Release(2);//Acknowledge
	}

}

void CPU2_ISR_from_IPC_Channel3(void)
{
	if(1 /* if notify status is set in the HW register. */)
	{
		CPU2_Check_IPC_Notification(3);//Acknowledge

		CPU2_Read_IPC_RegData(3, &CPU2_IpcMessage);
	}

	if(1 /* if release status is set in the HW register. */)
	{
		u16Channel1_Ack = CPU2_Check_IPC_Release(3);//Acknowledge
	}

}
/*****************************************/
