################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/I2C/I2C.c" \

C_SRCS += \
../Sources/Drivers/I2C/I2C.c \

OBJS += \
./Sources/Drivers/I2C/I2C.o \

C_DEPS += \
./Sources/Drivers/I2C/I2C.d \

OBJS_QUOTED += \
"./Sources/Drivers/I2C/I2C.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/I2C/I2C.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/I2C/I2C.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/I2C/I2C.o: ../Sources/Drivers/I2C/I2C.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/I2C/I2C.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/I2C/I2C.o"
	@echo 'Finished building: $<'
	@echo ' '


