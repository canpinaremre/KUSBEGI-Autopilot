################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/lib/rc_input/rc_input_mixer.c \
../Core/Inc/lib/rc_input/rc_input_sbus.c 

OBJS += \
./Core/Inc/lib/rc_input/rc_input_mixer.o \
./Core/Inc/lib/rc_input/rc_input_sbus.o 

C_DEPS += \
./Core/Inc/lib/rc_input/rc_input_mixer.d \
./Core/Inc/lib/rc_input/rc_input_sbus.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/lib/rc_input/rc_input_mixer.o: ../Core/Inc/lib/rc_input/rc_input_mixer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/lib/rc_input/rc_input_mixer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Inc/lib/rc_input/rc_input_sbus.o: ../Core/Inc/lib/rc_input/rc_input_sbus.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/lib/rc_input/rc_input_sbus.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

