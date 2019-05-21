################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/LCD/LCD.c" \
"../Sources/Drivers/LCD/s401.c" \

C_SRCS += \
../Sources/Drivers/LCD/LCD.c \
../Sources/Drivers/LCD/s401.c \

OBJS += \
./Sources/Drivers/LCD/LCD.o \
./Sources/Drivers/LCD/s401.o \

C_DEPS += \
./Sources/Drivers/LCD/LCD.d \
./Sources/Drivers/LCD/s401.d \

OBJS_QUOTED += \
"./Sources/Drivers/LCD/LCD.o" \
"./Sources/Drivers/LCD/s401.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/LCD/LCD.d" \
"./Sources/Drivers/LCD/s401.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/LCD/LCD.o \
./Sources/Drivers/LCD/s401.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/LCD/LCD.o: ../Sources/Drivers/LCD/LCD.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/LCD/LCD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/LCD/LCD.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/LCD/s401.o: ../Sources/Drivers/LCD/s401.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/LCD/s401.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/LCD/s401.o"
	@echo 'Finished building: $<'
	@echo ' '


