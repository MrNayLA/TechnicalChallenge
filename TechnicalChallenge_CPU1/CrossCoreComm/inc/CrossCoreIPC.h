/*
 * CrossCoreIPC.h
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#ifndef TECHNICALCHALLENGE_CPU1_CROSSCOREIPC_H_
#define TECHNICALCHALLENGE_CPU1_CROSSCOREIPC_H_

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
void CPU1_IPC_Init(uint8_t ChannelNo);

uint8_t CPU1_Acquire_IPC_Lock(uint8_t ChannelNo);

void CPU1_Notify_IPC(uint8_t ChannelNo);

void CPU1_SendMessage_IPC(uint8_t ChannelNo,char *Addr, uint32_t DataSize);

void CPU1_SendAck(uint8_t ChannelNo);

uint8_t CPU1_Release_IPC_Lock(uint8_t ChannelNo);


#endif /* TECHNICALCHALLENGE_CPU1_CROSSCOREIPC_H_ */
