################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CrossCoreCommTests/src/CrossCoreTestFunctions.c 

C_DEPS += \
./CrossCoreCommTests/src/CrossCoreTestFunctions.d 

OBJS += \
./CrossCoreCommTests/src/CrossCoreTestFunctions.o 


# Each subdirectory must supply rules for building sources it contributes
CrossCoreCommTests/src/%.o: ../CrossCoreCommTests/src/%.c CrossCoreCommTests/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../TechnicalChanllenge_TFR/unity/src -I../../TechnicalChanllenge_TFR/CPU1_CrossCoreComm/inc -I../../TechnicalChanllenge_TFR/CPU2_CrossCoreComm/inc -I../../TechnicalChanllenge_TFR/CrossCoreCommTests/inc -I../../TechnicalChanllenge_TFR/Common_Config -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-CrossCoreCommTests-2f-src

clean-CrossCoreCommTests-2f-src:
	-$(RM) ./CrossCoreCommTests/src/CrossCoreTestFunctions.d ./CrossCoreCommTests/src/CrossCoreTestFunctions.o

.PHONY: clean-CrossCoreCommTests-2f-src

