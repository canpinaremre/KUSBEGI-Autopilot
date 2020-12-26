################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/Inc/module/utility/subdir.mk
-include Core/Inc/module/send_message/subdir.mk
-include Core/Inc/module/i2c/subdir.mk
-include Core/Inc/lib/rc_input/subdir.mk
-include Core/Inc/lib/pid/subdir.mk
-include Core/Inc/lib/output_mixer/subdir.mk
-include Core/Inc/lib/kusbegi_autopilot/subdir.mk
-include Core/Inc/drivers/imu/subdir.mk
-include Core/Inc/drivers/BNO055/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Kusbegi-Autopilot.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Kusbegi-Autopilot.list \

OBJCOPY_BIN += \
Kusbegi-Autopilot.bin \


# All Target
all: Kusbegi-Autopilot.elf secondary-outputs

# Tool invocations
Kusbegi-Autopilot.elf: $(OBJS) $(USER_OBJS) D:\Work\KUSBEGI-Autopilot\STM32F407VGTX_FLASH.ld
	arm-none-eabi-gcc -o "Kusbegi-Autopilot.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\Work\KUSBEGI-Autopilot\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Kusbegi-Autopilot.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Kusbegi-Autopilot.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Kusbegi-Autopilot.list"
	@echo 'Finished building: $@'
	@echo ' '

Kusbegi-Autopilot.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Kusbegi-Autopilot.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
