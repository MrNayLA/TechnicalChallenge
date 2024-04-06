################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CPU2_CrossCoreComm/src/CPU2_CrossCoreIPC.c \
../CPU2_CrossCoreComm/src/CPU2_CrossCoreMemAPI.c \
../CPU2_CrossCoreComm/src/CPU2_CrossCoreOs.c 

C_DEPS += \
./CPU2_CrossCoreComm/src/CPU2_CrossCoreIPC.d \
./CPU2_CrossCoreComm/src/CPU2_CrossCoreMemAPI.d \
./CPU2_CrossCoreComm/src/CPU2_CrossCoreOs.d 

OBJS += \
./CPU2_CrossCoreComm/src/CPU2_CrossCoreIPC.o \
./CPU2_CrossCoreComm/src/CPU2_CrossCoreMemAPI.o \
./CPU2_CrossCoreComm/src/CPU2_CrossCoreOs.o 


# Each subdirectory must supply rules for building sources it contributes
CPU2_CrossCoreComm/src/%.o: ../CPU2_CrossCoreComm/src/%.c CPU2_CrossCoreComm/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../TechnicalChanllenge_TFR/CPU1_CrossCoreComm/inc -I../../TechnicalChanllenge_TFR/Common_Config -I../../TechnicalChanllenge_TFR/CPU2_CrossCoreComm/inc -I../../TechnicalChanllenge_TFR/unity/src -I../../TechnicalChanllenge_TFR/CrossCoreCommTests/inc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CPU2_CrossCoreComm-2f-src

clean-CPU2_CrossCoreComm-2f-src:
	-$(RM) ./CPU2_CrossCoreComm/src/CPU2_CrossCoreIPC.d ./CPU2_CrossCoreComm/src/CPU2_CrossCoreIPC.o ./CPU2_CrossCoreComm/src/CPU2_CrossCoreMemAPI.d ./CPU2_CrossCoreComm/src/CPU2_CrossCoreMemAPI.o ./CPU2_CrossCoreComm/src/CPU2_CrossCoreOs.d ./CPU2_CrossCoreComm/src/CPU2_CrossCoreOs.o

.PHONY: clean-CPU2_CrossCoreComm-2f-src

