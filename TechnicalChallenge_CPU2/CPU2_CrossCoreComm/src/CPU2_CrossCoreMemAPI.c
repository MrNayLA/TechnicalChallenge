/*
 * CrossCoreMemAPI.c
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#include <stdlib.h>
#include <string.h>

#include "CPU2_CrossCoreConfig.h"
#include "CPU2_CrossCoreIPC.h"
#include "CPU2_CrossCoreOs.h"


/* This is the API to read data from shared memory, parse the data and pass it to user's buffer. */
uint16_t CPU2_ReadSharedMemory(char *userbuff, char *src, uint32_t ByteSize)/* char is uint16_t in 16 bit addressable CPU */
{
	uint16_t RetFlag = 0;

	/* uint16_t is viewed as 1 byte in 16-bit addressable CPU, e.g, sizeof(uint16_t) = 1  */
	/* uint16_t */ char dest[ByteSize];/* Note: char is 16 bits in 16-bit addressable CPU. sizeof(char) = 1, but 16 bit wide */

	/* uint16_t */ char tempSrcBuff[ByteSize * 2];/* Temporarily used the local buffer which is double the size of the copied bytes(16-bit addressable). */

	if(CPU2_Acquire_IPC_Lock(UsedIPCChannel) == 1)/* Acquire IPC channel and lock. */
	{

		/* Read from shared memory into local buffer before parsing. */
		Enter_CriticalSection();/* Enter critical section to avoid data corruption */
		memcpy(dest, src, ByteSize);
		Exit_CriticalSection();/* Exit critical section after data-write */

		/* Parsing the data to match with 16-bit addressable CPU architecture */
		for(int i=0;i<ByteSize;i++)
		{
			/* 16-bits */ tempSrcBuff[i*2] = dest[i] & (0xff);/* Take lower 8 bits */
			/* 16-bits */ tempSrcBuff[(i*2)+1] = (dest[i] >> 8) & (0xff);/* Take higher 8 bits */
		}

		/* The below demonstrates how parsing algorithm was performed in the above loop. */
		//tempSrcBuff[0] /* 16-bits */ = dest[0] & (0xff);/* Take lower 8 bits */
		//tempSrcBuff[1] /* 16-bits */ = (dest[0] >> 8) & (0xff);/* Take higher 8 bits */

		//tempSrcBuff[2] /* 16-bits */ = dest[1] & (0xff);/* Take lower 8 bits */
		//tempSrcBuff[3] /* 16-bits */ = (dest[1] >> 8) & (0xff);/* Take higher 8 bits */

		//tempSrcBuff[4] /* 16-bits */ = dest[2] & (0xff);/* Take lower 8 bits */
		//tempSrcBuff[5] /* 16-bits */ = (dest[2] >> 8) & (0xff);/* Take higher 8 bits */


		/* Copy parsed data(tempSrcBuff) into user's buffer. */
		memcpy(userbuff, tempSrcBuff, (ByteSize*2));

		/* Acknowledge back to CPU1 after reading from shared memory and passing the parsed data to user's buffer. */
		CPU2_SendAck(UsedIPCChannel);
		CPU2_Release_IPC_Lock(UsedIPCChannel);/* Release the IPC lock and notify to another core(CPU1). */

		RetFlag = 1;

	}else{

		RetFlag = 0;

	}

    return RetFlag;
}
