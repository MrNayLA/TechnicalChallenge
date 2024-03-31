/*
 * CrossCoreMemAPI.c
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CrossCoreConfig.h"
#include "CrossCoreOs.h"
#include "CrossCoreIPC.h"


//extern uint8_t Channel1_Noti;
extern uint8_t Channel1_Ack;

/* 8-bit addressable in CPU1 */
uint8_t CPU1_WriteDataSharedMem(char *dest, char *src, uint32_t ByteSize)
{
	uint8_t RetFlag = 0;

	if(ByteSize <= (512/sizeof(char)))//if <=64, char is 8-bit wide here.
	{
		if(CPU1_Acquire_IPC_Lock(UsedIPCChannel) == 1)/* Acquire IPC channel and lock. */
		{
			CPU1_Notify_IPC_Lock(UsedIPCChannel);/* Notify to other core after IPC lock. */

			Enter_CriticalSection();/* Enter critical section to avoid data corruption */
			memcpy(dest, src, ByteSize);
			Exit_CriticalSection();/* Exit critical section after data-write */

			CPU1_Release_IPC_Lock(UsedIPCChannel);/* Release the IPC lock and notify to another core. */

			RetFlag = 1;
		}
		else{

			RetFlag = 0;
		}

	}else{//if >= 64

		uint32_t round = ByteSize / (512/sizeof(char));// ByteSize/64
		uint32_t remainingSize = ByteSize % (512/sizeof(char));

		for(int i=0;i<round;i++)
		{
			if(CPU1_Acquire_IPC_Lock(UsedIPCChannel) == 1)/* Acquire IPC channel and lock. */
			{
				CPU1_Notify_IPC_Lock(UsedIPCChannel);/* Notify to other core after IPC lock. */

				Enter_CriticalSection();/* Enter critical section to avoid data corruption */
				memcpy(dest, &src[i * (512/sizeof(char))], ByteSize);
				Exit_CriticalSection();/* Exit critical section after data-write */

				CPU1_Release_IPC_Lock(UsedIPCChannel);/* Release the IPC lock and notify to another core. */

				while(Channel1_Ack != 1)//Check acknowledgement from CPU2
				{
					//Wait until CPU2 acknowledge after reading the data from shared memory.
					//Probably, timeout checking mechanism can be implemented here.
				}

				RetFlag = 1;

			}else{

				RetFlag = 0;
			}

		}

		if(remainingSize != 0)//if there is remaining item
		{
			if(CPU1_Acquire_IPC_Lock(UsedIPCChannel) == 1)/* Acquire IPC channel and lock. */
			{
				CPU1_Notify_IPC_Lock(UsedIPCChannel);/* Notify to other core after IPC lock. */

				Enter_CriticalSection();/* Enter critical section to avoid data corruption */
				memcpy(dest, &src[(512/sizeof(char))], remainingSize);
				Exit_CriticalSection();/* Exit critical section after data-write */

				CPU1_Release_IPC_Lock(UsedIPCChannel);/* Release the IPC lock and notify to another core. */

				RetFlag = 1;

			}else{

				RetFlag = 0;

			}

		}

	}

	return RetFlag;
}
