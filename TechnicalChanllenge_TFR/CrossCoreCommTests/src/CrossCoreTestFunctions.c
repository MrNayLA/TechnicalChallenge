/*
 * CrossCoreTestFunctions.c
 *
 *  Created on: 5 Apr 2024
 *      Author: nayla
 */

#include "CPU1_CrossCOreMemAPI.h"
#include "CPU2_CrossCOreMemAPI.h"

#include <stdlib.h>
#include <string.h>
#include "CrossCoreConfig.h"
#include "CPU2_CrossCoreIPC.h"
#include "CrossCoreTestFunctions.h"
#include "unity.h"


/* Declaration of test variables */
/*********************************************************************************/
/* Data buffer to be written to shared memory */
volatile char cpu1_source[] = {"Welcome!"};//{'W','e','l','c','o','m','e','!','\0'}, String is just an array of characters.
volatile char cpu1_destination[(NumOfSharedMemoryBits/8)];/* 512/8 = 64 in 8-bit addressable CPU */


volatile char cpu1_source_more[] = {"Hello! Good day everyone! Stay hungry, stay foolish!"};

/*********************************************************************************/
//Source, here 1-byte is viewed as 16 bits in 16-bit addressable CPU.
/* String is an array of characters ending with '\0'. */
//volatile char cpu2_Source[]= "Hello!";//{'H','e','l','l','o','!','\0'};//Simulated as shared memory for stand-alone test
volatile char cpu2_Source[(NumOfSharedMemoryBits/8)];

//User's buffer, here 1-byte is viewed as 16 bits in 16-bit addressable CPU.
//Allocate the size of UserBuffer as double the size of source data.
volatile char cpu2_UserBuffer[sizeof(cpu2_Source)*2];/* This is user's buffer to store parsed data. */

/*********************************************************************************/

extern uint8_t CPU1_TestLockStatus;
extern uint8_t CPU2_TestLockStatus;

extern IPC_Msg_t CPU2_IpcMessage;

/*******************************************
 * Must declare setUp() & tearDown functions
 * *****************************************/
//Run before a particular test prepare the need.
void setUp(void)
{
	/* For testing purpose, copy written shared data to cpu2_Source to simulate as a shared memory. */
	memcpy(cpu2_Source, cpu1_destination, sizeof(cpu1_destination));

	//From CPU1, the data length(size) to be read should be passed via IPC to CPU2.

	/* Later these data from the shared memory will be read and parsed in CPU2's Read API.  */

	//To simulate to get updated data from IPC registers.
	// Assume that CPU2_ISR_from_IPC_Channel1() has been called and serviced.
	// The below variables will be updated there.
	CPU2_IpcMessage.ptrMessage = &cpu2_Source;
	CPU2_IpcMessage.MsgInfo.bit_view.MessageSize = sizeof(cpu2_Source);

	/************************************************************/

}

//Run after the tests
void tearDown(void)
{
	//Nothing to do for now
	/* Clear test memories after test. */
	memset((void *)&cpu1_source,0,sizeof(cpu1_source));
	memset((void *)&cpu1_destination,0,sizeof(cpu1_destination));
	memset((void *)&cpu2_Source,0,sizeof(cpu2_Source));
	memset((void *)&cpu2_UserBuffer,0,sizeof(cpu2_UserBuffer));
}
/**************************/


/* Test#1_1, Testing data write to shared memory in CPU1 */
void Test1_1_SharedMemoryWrite(void)
{
	uint8_t u8RetVal = 0;

	CPU1_TestLockStatus = 1;//Simulated IPC channel Lock.

	u8RetVal = CPU1_WriteDataSharedMemory(cpu1_destination, cpu1_source, sizeof(cpu1_source));

	CPU1_TestLockStatus = 0;//Simulated IPC channel Unlock.

	/* Check whether write-process has been successful or not. */
	TEST_ASSERT_EQUAL(1, u8RetVal);

}

/* Test#1_2, Verify written data within CPU1. */
void Test1_2_VerifyWrittenData(void)
{
	int iRetVal = 0;

	/* Verify by comparing destination data against source data after being written in Test#1. */
	iRetVal = memcmp(cpu1_destination, cpu1_source, sizeof(cpu1_source));

	//iRetVal > 0 :cpu1_source is less than cpu1_destination
	//iRetVal < 0 :cpu1_destination is less than cpu1_source
	//iRetVal == 0 :cpu1_destination is equal to cpu1_source

	TEST_ASSERT_EQUAL(0, iRetVal);

	printf("\nCPU1: Data written to shared memory ->> ");
	for(int i=0;i< sizeof(cpu1_destination);i++)
	{
		/* This is to display the data written. */
		printf("%c", (char)cpu1_destination[i]);//Just to verify data in 8-bit addressable mode in the PC
	}
	printf("\n\r");

}

/* Test#1_3, Testing data write to shared memory in CPU1 with IPC Lock not acquired condition */
void Test1_3_SharedMemoryWrite(void)
{
	uint8_t u8RetVal = 0;

	/* Purposely failed the lock. */
	CPU1_TestLockStatus = 0;//Simulated IPC channel Lock.

	u8RetVal = CPU1_WriteDataSharedMemory(cpu1_destination, cpu1_source_more, sizeof(cpu1_source_more));

	CPU1_TestLockStatus = 0;//Simulated IPC channel Unlock.

	/* Check whether write-process has been successful or not. */
	TEST_ASSERT_EQUAL(0, u8RetVal);
	/* Write-process should be failed here, return 0, and then test passes. */

}

/* Test#2_1, Testing data read from shared memory in CPU2, parse 16-bit addressable data and pass data to user's buffer. */
void Test2_1_ReadFromSharedMemory(void)
{
	uint16_t u16RetVal = 0;

	CPU2_TestLockStatus = 1;//Simulated IPC channel Lock.

	//u16RetVal = CPU2_ReadSharedMemory(&cpu2_UserBuffer, &cpu2_Source, sizeof(cpu2_Source));
	u16RetVal = CPU2_ReadSharedMemory(&cpu2_UserBuffer, CPU2_IpcMessage.ptrMessage, CPU2_IpcMessage.MsgInfo.bit_view.MessageSize);

	CPU2_TestLockStatus = 0;//Simulated IPC channel Unlock.

	/* Check whether read process has been successful or not. */
	TEST_ASSERT_EQUAL(1, u16RetVal);

}

/* Test#2_2, This is to verify the data read from CPU2 and parsing. */
void Test2_2_VerifyReadData(void)
{
	int iRetVal = 0;
	uint32_t Cnt = 0;

	for(int i=0;i<sizeof(cpu2_Source);i++)
	{
		if(cpu2_Source[i] == cpu2_UserBuffer[i*2])
		{
			Cnt++;
		}

		//if(cpu2_Source[0] == cpu2_UserBuffer[0]),  cpu2_UserBuffer[1]
		//if(cpu2_Source[1] == cpu2_UserBuffer[2]),  cpu2_UserBuffer[3]
		//if(cpu2_Source[2] == cpu2_UserBuffer[4]),  cpu2_UserBuffer[5]
		//if(cpu2_Source[3] == cpu2_UserBuffer[6]),  cpu2_UserBuffer[7]
		//....
		//....
	}

	if(Cnt == sizeof(cpu2_Source))
	{
		iRetVal = 1;

	}else{

		iRetVal = 0;
	}

	TEST_ASSERT_EQUAL(1, iRetVal);


	/* Verification */
	printf("\nCPU2: Size of Shared Source Data %d bytes",sizeof(cpu2_Source));
	printf("\nCPU2: Size of UserBuffer %d bytes\n",sizeof(cpu2_UserBuffer));
	printf("CPU2: Parsed array of characters read from shared memory ->> ");
	for(int i=0;i< sizeof(cpu2_UserBuffer);i++)
	{
		/* This is to display already-parsed data. */
		printf("%c", (char)cpu2_UserBuffer[i]);//Just to simulate/verify like 8-bit addressable mode in the PC
	}
	printf("\n\r");

}

/* Test#2_3, Testing data read from shared memory in CPU2, parse 16-bit addressable data and pass data to user's buffer. */
void Test2_3_ReadFromSharedMemory(void)
{
	uint16_t u16RetVal = 0;

	/* Purposely failed the lock. */
	CPU2_TestLockStatus = 0;//Simulated IPC channel Unlock.

	//u16RetVal = CPU2_ReadSharedMemory(&cpu2_UserBuffer, &cpu2_Source, sizeof(cpu2_Source));
	u16RetVal = CPU2_ReadSharedMemory(&cpu2_UserBuffer, CPU2_IpcMessage.ptrMessage, CPU2_IpcMessage.MsgInfo.bit_view.MessageSize);

	CPU2_TestLockStatus = 0;//Simulated IPC channel Unlock.

	/* Check whether read process has been successful or not. */
	TEST_ASSERT_EQUAL(0, u16RetVal);

}
