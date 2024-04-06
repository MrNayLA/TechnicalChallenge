/*
 * CrossCoreIPC.h
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#ifndef TECHNICALCHALLENGE_CPU2_CROSSCOREIPC_H_
#define TECHNICALCHALLENGE_CPU2_CROSSCOREIPC_H_

#include <stdlib.h>



/*****************************************/
void CPU2_IPC_Init(uint16_t ChannelNo);

uint16_t CPU2_Acquire_IPC_Lock(uint16_t ChannelNo);

void CPU2_Notify_IPC_Lock(uint16_t ChannelNo);

void CPU2_SendMessage_IPC(uint16_t ChannelNo,char *Addr, uint32_t DataSize);

void CPU2_SendAck(uint16_t ChannelNo);

void CPU2_Read_IPC_RegData(uint16_t ChannelNo, IPC_Msg_t* ptrIpcMsg);

uint16_t CPU2_Release_IPC_Lock(uint16_t ChannelNo);



#endif /* TECHNICALCHALLENGE_CPU2_CROSSCOREIPC_H_ */
