/*
 * CrossCoreConfig.h
 *
 *  Created on: 30 Mar 2024
 *      Author: nayla
 */

#ifndef TECHNICALCHALLENGE_TFR_CROSSCORECONFIG_H_
#define TECHNICALCHALLENGE_TFR_CROSSCORECONFIG_H_


#define UsedIPCChannel					(1u)/* Channel number of assumed IPC HW for multi-core communication and synchronisation */


#define CPU1SharedMemStartAddress		(volatile char *)(0x20000000u)/* Start address of shared memory block#1 from CPU1 */
#define CPU1SharedMemEndAddress			(volatile char *)(0x20000040u)/* End address of shared memory block#1 from CPU1 */

#define CPU2SharedMemStartAddress		(volatile char *)(0x00080010u)/* Start address of shared memory block#2 from CPU2 */
#define CPU2SharedMemEndAddress			(volatile char *)(0x00080030u)/* End address of shared memory block#2 from CPU2 */

#define NumOfSharedMemoryBits			(512u)/* Total number of bits of the shared memory */


#define SimulatedTestEnabled			(1u)/* Enable or disable simulated test */


/***************************************************************/
/* Assume the IPC channel has the following two data registers. */
#define IPC_DataReg1	(volatile uint32_t *)(0xFFFF0001u)
#define IPC_DataReg2	(volatile uint32_t *)(0xFFFF0002u)



extern void SuspendInterrupts(void);
extern void ResumeInterrupts(void);

#define Enter_CriticalSection()		//SuspendInterrupts()
#define Exit_CriticalSection()		//ResumeInterrupts()


typedef enum{

	enSendNotify = 0,
	enSendAck = 1,
	enReciveAck = 2

}IPC_MsgID_t;

/* Assume the each IPC channel has two 32-bit wise data registers. */
typedef volatile struct IPC_Msg{

	const char* ptrMessage;

	union MsgInfo_tag
	{
		uint32_t u32_view;

		struct
		{
			uint32_t MessageSize:16;//Bit<0 ~ 15>
			uint32_t Identifier:16;//Bit<16 ~ 31>

		}bit_view;

	}MsgInfo;

}IPC_Msg_t;

/**************************************************/
// If we plan to use the below method (defining linker sections in the intended memory area),
// respective sections should have been defined and already configured in the linker file.
// But for now, I have no info about the actual MCUs and corresponding available memory map,
// it is not possible to implement the below method and chose the above way to access the memory area
// <0x20000000 ~ 0x20000040> and <0x00080010 ~ 0x00080030>
/**************************************************/
//Example:
//#pragma ghs section bss =".shared_mem_section1"
//uint8_t u8CPU1SharedMem[64];
//#pragma ghs section bss = default

//#pragma ghs section bss =".shared_mem_section2"
//uint8_t u8CPU2SharedMem[64];
//#pragma ghs section bss = default
/**************************************************/


#endif /* TECHNICALCHALLENGE_TFR_CROSSCORECONFIG_H_ */
