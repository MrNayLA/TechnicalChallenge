################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../unity/src/unity.c 

C_DEPS += \
./unity/src/unity.d 

OBJS += \
./unity/src/unity.o 


# Each subdirectory must supply rules for building sources it contributes
unity/src/%.o: ../unity/src/%.c unity/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../../TechnicalChanllenge_TFR/CPU1_CrossCoreComm/inc -I../../TechnicalChanllenge_TFR/Common_Config -I../../TechnicalChanllenge_TFR/CPU2_CrossCoreComm/inc -I../../TechnicalChanllenge_TFR/unity/src -I../../TechnicalChanllenge_TFR/CrossCoreCommTests/inc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-unity-2f-src

clean-unity-2f-src:
	-$(RM) ./unity/src/unity.d ./unity/src/unity.o

.PHONY: clean-unity-2f-src

