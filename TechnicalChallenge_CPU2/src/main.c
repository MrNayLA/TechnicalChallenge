/*
 ============================================================================
 Name        : TechnicalChallenge_CPU2.c
 Author      : NayLA
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "CrossCoreConfig.h"
#include "CrossCoreIPC.h"
#include "CrossCoreMemAPI.h"


/* 512 bits = 64 bytes in 8-bit addressable core */
/* 512 bits = 32 bytes in 16-bit addressable core */
/* 1 byte is considered to be 16 bits in 16-bit addressable architecture */
/* Each address in memory references 16-bits of data. */


//Source, here 1-byte is viewed as 16 bits in 16-bit addressable CPU.
/* String is an array of characters ending with '\0'. */
volatile char Source[] = "Hello!";//{'H','e','l','l','o','!','\0'};//Used for stand-alone test

//User's buffer, here 1-byte is viewed as 16 bits in 16-bit addressable CPU.
//Allocate the size of UserBuffer as double the size of source data.
volatile char UserBuffer[sizeof(Source)*2];/* This is user's buffer to store parsed data. */


int main(void) {

	puts("\n16-bit addressable CPU2 Code: \n"); /* Print the core name. */

	/* Initialise HW IPC channel used for inter-processor communication. */
	CPU2_IPC_Init(UsedIPCChannel);


	/* Write data to the shared memory area. It is important to use "sizeof(x)" here,
	 * otherwise, it will calculate the size wrongly. */
#if SimulatedTestEnabled == 1
	CPU2_ReadSharedMemory(&UserBuffer, &Source, sizeof(Source));/* Write to shared memory after IPC lock */
#else
	/* Cannot use hard-coded value for the buffer size. Must use sizeof(x). Otherwise, it will give wrong value of size. */
	CPU2_ReadSharedMemory(&UserBuffer, (char *)CPU2SharedMemStartAddress, sizeof(UserBuffer));/* Write to shared memory after IPC lock */
#endif

	/* Verification */
	printf("\nSize of UserBuffer %d\n",sizeof(UserBuffer));
	printf("Parsed array of characters ->> ");
	for(int i=0;i< sizeof(UserBuffer);i++)
	{
		/* This is to display already-parsed data. */
		printf("%c", (char)UserBuffer[i]);//Just to simulate/verify like 8-bit addressable mode in the PC
	}


	return EXIT_SUCCESS;
}
