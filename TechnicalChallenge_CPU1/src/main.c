/*
 ============================================================================
 Name        : main.c
 Author      : NayLA
 Version     :
 Copyright   : Your copyright notice
 Description : Cross core communication Demo - TechnicalChallenge, CPU1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CPU1_CrossCoreConfig.h"
#include "CPU1_CrossCoreIPC.h"
#include "CPU1_CrossCoreMemAPI.h"



/* 512 bits = 64 bytes in 8-bit addressable core */
/* 1 byte is considered to be 8 bits in 8-bit addressable architecture */
/* Each address in memory references 8-bits of data. */

/* Data buffer to be written to shared memory */
volatile char source[] = {"Welcome!"};//{'W','e','l','c','o','m','e','!','\0'}, String is just an array of characters.
volatile char destination[(NumOfSharedMemoryBits/8)];/* 512/8 = 64 in 8-bit addressable CPU */


int main(void) {

	puts("\n8-bit addressable CPU1 Code: \n"); /* Print the core name. */

	/* Initialize HW IPC channel used for inter-processor communication. */
	CPU1_IPC_Init(UsedIPCChannel);


	/* Write data to the shared memory area. */
#if SimulatedTestEnabled == 1
	/* *
	 * Assume that destination[x] has already been located in the specified shared memory address address
	 * (0x20000000 ~ 0x20000040) or (0x80010 ~ 0x80030)
	 * */
	CPU1_WriteDataSharedMemory(destination, source, sizeof(source));/* Write to shared memory after IPC lock */
#else
	/* Test with actual shared memory address (destination). This will only work with actual system. */
	CPU1_WriteDataSharedMemory((char *)CPU1SharedMemStartAddress, source, sizeof(source));/* Write to shared memory after IPC lock */
#endif

	/* Verification */
	printf("\nSize of shared memory = %d bytes\n", sizeof(destination));
	printf("Array of characters in shared memory(destination) ->> ");
	for(int i=0;i< sizeof(destination);i++)
	{
		printf("%c", (char)destination[i]);//Just to verify data written in 8-bit addressable CPU
	}

	printf("\nEnd of Test!");


	return EXIT_SUCCESS;
}
