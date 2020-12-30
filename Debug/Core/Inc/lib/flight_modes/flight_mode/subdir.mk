################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/lib/flight_modes/flight_mode/flight_mode.c 

OBJS += \
./Core/Inc/lib/flight_modes/flight_mode/flight_mode.o 

C_DEPS += \
./Core/Inc/lib/flight_modes/flight_mode/flight_mode.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/lib/flight_modes/flight_mode/flight_mode.o: ../Core/Inc/lib/flight_modes/flight_mode/flight_mode.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Inc/lib/flight_modes/flight_mode/flight_mode.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

