/*
 * CrossCoreIPC.h
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#ifndef TECHNICALCHALLENGE_CPU2_CROSSCOREIPC_H_
#define TECHNICALCHALLENGE_CPU2_CROSSCOREIPC_H_

#include <stdlib.h>

/* Assume the IPC channel has the following two data registers. */
#define IPC_DataReg1	(volatile uint32_t *)(0xFFFF0001u)
#define IPC_DataReg2	(volatile uint32_t *)(0xFFFF0002u)


typedef enum{

	enSendNotify = 0,
	enSendAck = 1,
	enReciveAck = 2

}IPC_MsgID_t;

/* Assume the each IPC channel has two 32-bit wise data registers. */
typedef volatile struct IPC_Msg{

	const char* ptrMessage;

	union MsgInfo_tag
	{
		uint32_t u32_view;

		struct
		{
			uint32_t MessageSize:16;
			uint32_t Identifier:16;

		}bit_view;

	}MsgInfo;

}IPC_Msg_t;


/*****************************************/
void CPU2_IPC_Init(uint16_t ChannelNo);

uint16_t CPU2_Acquire_IPC_Lock(uint16_t ChannelNo);

void CPU2_Notify_IPC_Lock(uint16_t ChannelNo);

void CPU2_SendMessage_IPC(uint16_t ChannelNo,char *Addr, uint32_t DataSize);

void CPU2_SendAck(uint16_t ChannelNo);

void CPU2_Read_IPC_RegData(uint16_t ChannelNo, IPC_Msg_t* ptrIpcMsg);

uint16_t CPU2_Release_IPC_Lock(uint16_t ChannelNo);



#endif /* TECHNICALCHALLENGE_CPU2_CROSSCOREIPC_H_ */
