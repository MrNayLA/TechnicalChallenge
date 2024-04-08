################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CPU1_CrossCoreComm/src/CPU1_CrossCoreIPC.c \
../CPU1_CrossCoreComm/src/CPU1_CrossCoreMemAPI.c \
../CPU1_CrossCoreComm/src/CPU1_CrossCoreOs.c 

C_DEPS += \
./CPU1_CrossCoreComm/src/CPU1_CrossCoreIPC.d \
./CPU1_CrossCoreComm/src/CPU1_CrossCoreMemAPI.d \
./CPU1_CrossCoreComm/src/CPU1_CrossCoreOs.d 

OBJS += \
./CPU1_CrossCoreComm/src/CPU1_CrossCoreIPC.o \
./CPU1_CrossCoreComm/src/CPU1_CrossCoreMemAPI.o \
./CPU1_CrossCoreComm/src/CPU1_CrossCoreOs.o 


# Each subdirectory must supply rules for building sources it contributes
CPU1_CrossCoreComm/src/%.o: ../CPU1_CrossCoreComm/src/%.c CPU1_CrossCoreComm/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../TechnicalChallenge_CPU1/CPU1_CrossCoreComm/inc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CPU1_CrossCoreComm-2f-src

clean-CPU1_CrossCoreComm-2f-src:
	-$(RM) ./CPU1_CrossCoreComm/src/CPU1_CrossCoreIPC.d ./CPU1_CrossCoreComm/src/CPU1_CrossCoreIPC.o ./CPU1_CrossCoreComm/src/CPU1_CrossCoreMemAPI.d ./CPU1_CrossCoreComm/src/CPU1_CrossCoreMemAPI.o ./CPU1_CrossCoreComm/src/CPU1_CrossCoreOs.d ./CPU1_CrossCoreComm/src/CPU1_CrossCoreOs.o

.PHONY: clean-CPU1_CrossCoreComm-2f-src

