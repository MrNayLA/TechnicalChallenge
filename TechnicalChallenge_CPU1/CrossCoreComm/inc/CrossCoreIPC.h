/*
 * CrossCoreIPC.h
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#ifndef TECHNICALCHALLENGE_CPU1_CROSSCOREIPC_H_
#define TECHNICALCHALLENGE_CPU1_CROSSCOREIPC_H_



void CPU1_IPC_Init(uint8_t ChannelNo);

uint8_t CPU1_Acquire_IPC_Lock(uint8_t ChannelNo);

void CPU1_Notify_IPC_Lock(uint8_t ChannelNo);

uint8_t CPU1_Release_IPC_Lock(uint8_t ChannelNo);


#endif /* TECHNICALCHALLENGE_CPU1_CROSSCOREIPC_H_ */
