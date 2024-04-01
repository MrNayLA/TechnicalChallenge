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
	uint32_t round = 0;
	uint32_t remainingSize = 0;
	uint32_t Cnt = 0;

	if(ByteSize <= (512/sizeof(char)))//if ByteSize<=64, char is 8-bit wide here.
	{
		if(CPU1_Acquire_IPC_Lock(UsedIPCChannel) == 1)/* Acquire IPC channel and lock. */
		{
			/* Copy data into shared memory. */
			Enter_CriticalSection();/* Enter critical section to avoid data corruption */
			memcpy(dest, src, ByteSize);
			Exit_CriticalSection();/* Exit critical section after data-write */

			/* Send message (Address and DataSize) via IPC channel to the other core. */
			CPU1_SendMessage_IPC(UsedIPCChannel, dest, ByteSize);

			/* Notify another core via IPC */
			CPU1_Notify_IPC(UsedIPCChannel);/* Notify to other core after sending data */
			CPU1_Release_IPC_Lock(UsedIPCChannel);/* Release the IPC lock and notify to another core. */

			//Check acknowledgement from CPU2 and some wait/timeout delay
			do{
				//Wait until CPU2 acknowledge after reading the data from shared memory.
				//Probably, timeout checking mechanism can be implemented here.
				Cnt++;

				/* Channel1_Ack should be updated in the ISR. */
			}while((Channel1_Ack != 1)||(Cnt >= 5000));

			/* The above can be replaced with OS event in case of system with OS configuration. */

			RetFlag = 1;
		}
		else{

			RetFlag = 0;
		}

	}else{//if ByteSize>=64

		round = ByteSize / (512/sizeof(char));// ByteSize/64
		remainingSize = ByteSize % (512/sizeof(char));

		for(int i=0;i<round;i++)
		{
			if(CPU1_Acquire_IPC_Lock(UsedIPCChannel) == 1)/* Acquire IPC channel and lock. */
			{
				/* Copy data into shared memory. */
				Enter_CriticalSection();/* Enter critical section to avoid data corruption */
				memcpy(dest, &src[i * (512/sizeof(char))], ByteSize);
				Exit_CriticalSection();/* Exit critical section after data-write */

				/* Send message (Address and DataSize) via IPC channel to the other core. */
				CPU1_SendMessage_IPC(UsedIPCChannel, dest, ByteSize);

				/* Notify another core via IPC */
				CPU1_Notify_IPC(UsedIPCChannel);/* Notify to other core after sending data */
				CPU1_Release_IPC_Lock(UsedIPCChannel);/* Release the IPC lock and notify to another core. */

				//Check acknowledgement from CPU2 and some wait/timeout delay
				do{
					//Wait until CPU2 acknowledge after reading the data from shared memory.
					//Probably, timeout checking mechanism can be implemented here.
					Cnt++;

					/* Channel1_Ack should be updated in the ISR. */
				}while((Channel1_Ack != 1)||(Cnt >= 5000));

				/* The above can be replaced with OS event in case of system with OS configuration. */

				RetFlag = 1;

			}else{

				RetFlag = 0;
			}

		}

		if(remainingSize != 0)//if there is remaining item
		{
			if(CPU1_Acquire_IPC_Lock(UsedIPCChannel) == 1)/* Acquire IPC channel and lock. */
			{
				/* Copy data into shared memory. */
				Enter_CriticalSection();/* Enter critical section to avoid data corruption */
				memcpy(dest, &src[(512/sizeof(char))], remainingSize);
				Exit_CriticalSection();/* Exit critical section after data-write */

				/* Send message (Address and DataSize) via IPC channel to the other core. */
				CPU1_SendMessage_IPC(UsedIPCChannel, dest, ByteSize);

				/* Notify another core via IPC */
				CPU1_Notify_IPC(UsedIPCChannel);/* Notify to other core after sending data */
				CPU1_Release_IPC_Lock(UsedIPCChannel);/* Release the IPC lock and notify to another core. */

				//Check acknowledgement from CPU2 and some wait/timeout delay
				do{
					//Wait until CPU2 acknowledge after reading the data from shared memory.
					//Probably, timeout checking mechanism can be implemented here.
					Cnt++;

					/* Channel1_Ack should be updated in the ISR. */
				}while((Channel1_Ack != 1)||(Cnt >= 5000));

				/* The above can be replaced with OS event in case of system with OS configuration. */

				RetFlag = 1;

			}else{

				RetFlag = 0;

			}

		}

	}

	return RetFlag;
}
