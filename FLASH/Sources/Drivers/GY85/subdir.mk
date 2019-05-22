################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/GY85/GY85.c" \

C_SRCS += \
../Sources/Drivers/GY85/GY85.c \

OBJS += \
./Sources/Drivers/GY85/GY85.o \

C_DEPS += \
./Sources/Drivers/GY85/GY85.d \

OBJS_QUOTED += \
"./Sources/Drivers/GY85/GY85.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/GY85/GY85.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/GY85/GY85.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/GY85/GY85.o: ../Sources/Drivers/GY85/GY85.c
	@echo 'Building file: $<'
<<<<<<< Updated upstream
	@echo 'Executing target #11 $<'
=======
	@echo 'Executing target #12 $<'
>>>>>>> Stashed changes
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/GY85/GY85.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/GY85/GY85.o"
	@echo 'Finished building: $<'
	@echo ' '


