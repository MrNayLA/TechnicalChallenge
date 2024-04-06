/*
 ============================================================================
 Name        : TechnicalChanllenge_TFR.c
 Author      : NayLA
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

#include "unity.h"

#include "CPU1_CrossCOreMemAPI.h"
#include "CPU2_CrossCOreMemAPI.h"
#include "CrossCoreTestFunctions.h"



int main(void) {
	puts("Cross Core Communication Test frame:\n\r"); /* prints  */

	/* Start of test with Unity Test Framework */
	UNITY_BEGIN();

	 /*
	  * Add in between
	  * RUN_TEST(func_name);
	  */

		RUN_TEST(Test1_1_SharedMemoryWrite);

		RUN_TEST(Test1_2_VerifyWrittenData);

		RUN_TEST(Test1_3_SharedMemoryWrite);

		/* Setup and prepare variable and data as shared memory resource here before Read API call. */
		/* Simulate for receiving data as IPC message from HW LLD layer. */
		setUp();
		RUN_TEST(Test2_1_ReadFromSharedMemory);

		RUN_TEST(Test2_2_VerifyReadData);

		RUN_TEST(Test2_3_ReadFromSharedMemory);


		tearDown();

	UNITY_END();

	printf("\nEnd of Tests!\n");


	return EXIT_SUCCESS;
}
