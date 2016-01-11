################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32f4xx_it.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/main.o \
./src/stm32f4xx_it.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/main.d \
./src/stm32f4xx_it.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -DUSE_STDPERIPH_DRIVER=1 -IC:/Users/raven17yo/workspace/1/include -IC:/Users/raven17yo/workspace/1/system/include -IC:/Users/raven17yo/workspace/1/system/include/cmsis -IC:/Users/raven17yo/workspace/1/system/include/stm32f4-hal -IC:/Users/raven17yo/Desktop/Cpsb/stm32f4_dsp_stdperiph_lib/STM32F4xx_DSP_StdPeriph_Lib_V1.6.1/Libraries/CMSIS/Include -IC:/Users/raven17yo/Desktop/Cpsb/stm32f4_dsp_stdperiph_lib/STM32F4xx_DSP_StdPeriph_Lib_V1.6.1/Libraries/CMSIS/Device/ST/STM32F4xx/Include -IC:/Users/raven17yo/Desktop/Cpsb/stm32f4_dsp_stdperiph_lib/STM32F4xx_DSP_StdPeriph_Lib_V1.6.1/Libraries/STM32F4xx_StdPeriph_Driver/inc -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


