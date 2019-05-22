################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/LSM9DS1/LSM9DS1.c" \

C_SRCS += \
../Sources/Drivers/LSM9DS1/LSM9DS1.c \

OBJS += \
./Sources/Drivers/LSM9DS1/LSM9DS1.o \

C_DEPS += \
./Sources/Drivers/LSM9DS1/LSM9DS1.d \

OBJS_QUOTED += \
"./Sources/Drivers/LSM9DS1/LSM9DS1.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/LSM9DS1/LSM9DS1.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/LSM9DS1/LSM9DS1.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/LSM9DS1/LSM9DS1.o: ../Sources/Drivers/LSM9DS1/LSM9DS1.c
	@echo 'Building file: $<'
<<<<<<< Updated upstream
	@echo 'Executing target #7 $<'
=======
	@echo 'Executing target #5 $<'
>>>>>>> Stashed changes
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/LSM9DS1/LSM9DS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/LSM9DS1/LSM9DS1.o"
	@echo 'Finished building: $<'
	@echo ' '


