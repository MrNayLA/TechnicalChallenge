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

#include "CrossCoreConfig.h"
#include "CrossCoreIPC.h"
#include "CrossCoreMemAPI.h"


/* 512 bits = 64 bytes in 8-bit addressable core */
/* 1 byte is considered to be 8 bits in 8-bit addressable architecture */
/* Each address in memory references 8-bits of data. */

volatile char source[64];/* Data buffer to be written to shared memory */
//volatile char destination[64];


int main(void) {

	puts("\n8-bit addressable CPU1 Code: \n"); /* Print the core name. */

	/* Initialize HW IPC channel used for inter-processor communication. */
	CPU1_IPC_Init(UsedIPCChannel);

	printf("\nDestination address -> 0x%x , Source address -> 0x%x \n\r", u32CPU1SharedMemStartAddress, &source);
	printf("Size of source data = %d \n",sizeof(source));

	/* Write data to the shared memory area. */
	CPU1_WriteDataSharedMem((char *)u32CPU1SharedMemStartAddress, (char *)&source, sizeof(source));/* Write to shared memory after IPC lock */



	return EXIT_SUCCESS;
}
