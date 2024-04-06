/*
 * CrossCoreTestFunctions.h
 *
 *  Created on: 5 Apr 2024
 *      Author: nayla
 */

#ifndef CROSSCORECOMMTESTS_INC_CROSSCORETESTFUNCTIONS_H_
#define CROSSCORECOMMTESTS_INC_CROSSCORETESTFUNCTIONS_H_


void setUp(void);

void tearDown(void);


/* (+) Test#1_1, Testing data write to shared memory */
void Test1_1_SharedMemoryWrite(void);

/* (+) Test#1_2, Verify written data within CPU1. */
void Test1_2_VerifyWrittenData(void);

/* (-)Test#1_1, Testing data write to shared memory with IPC lock not acquired condition. */
void Test1_3_SharedMemoryWrite(void);


/* (+) Test#2_1, Testing data read from shared memory, parse 16-bit addressable data and pass data to user's buffer. */
void Test2_1_ReadFromSharedMemory(void);

/* (+) Test#2_2, */
void Test2_2_VerifyReadData(void);

/* (-) Test#2_3, */
void Test2_3_ReadFromSharedMemory(void);



#endif /* CROSSCORECOMMTESTS_INC_CROSSCORETESTFUNCTIONS_H_ */
