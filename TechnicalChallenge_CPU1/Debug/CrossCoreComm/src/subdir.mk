################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CrossCoreComm/src/CrossCoreIPC.c \
../CrossCoreComm/src/CrossCoreMemAPI.c \
../CrossCoreComm/src/CrossCoreOs.c 

C_DEPS += \
./CrossCoreComm/src/CrossCoreIPC.d \
./CrossCoreComm/src/CrossCoreMemAPI.d \
./CrossCoreComm/src/CrossCoreOs.d 

OBJS += \
./CrossCoreComm/src/CrossCoreIPC.o \
./CrossCoreComm/src/CrossCoreMemAPI.o \
./CrossCoreComm/src/CrossCoreOs.o 


# Each subdirectory must supply rules for building sources it contributes
CrossCoreComm/src/%.o: ../CrossCoreComm/src/%.c CrossCoreComm/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../TechnicalChallenge_CPU1/CrossCoreComm/inc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CrossCoreComm-2f-src

clean-CrossCoreComm-2f-src:
	-$(RM) ./CrossCoreComm/src/CrossCoreIPC.d ./CrossCoreComm/src/CrossCoreIPC.o ./CrossCoreComm/src/CrossCoreMemAPI.d ./CrossCoreComm/src/CrossCoreMemAPI.o ./CrossCoreComm/src/CrossCoreOs.d ./CrossCoreComm/src/CrossCoreOs.o

.PHONY: clean-CrossCoreComm-2f-src

