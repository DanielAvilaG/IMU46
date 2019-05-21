################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \
"../Sources/wrappers.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/main.c \
../Sources/sa_mtb.c \
../Sources/wrappers.c \

OBJS += \
./Sources/Events.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/wrappers.o \

C_DEPS += \
./Sources/Events.d \
./Sources/main.d \
./Sources/sa_mtb.d \
./Sources/wrappers.d \

OBJS_QUOTED += \
"./Sources/Events.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \
"./Sources/wrappers.o" \

C_DEPS_QUOTED += \
"./Sources/Events.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \
"./Sources/wrappers.d" \

OBJS_OS_FORMAT += \
./Sources/Events.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/wrappers.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/wrappers.o: ../Sources/wrappers.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/wrappers.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/wrappers.o"
	@echo 'Finished building: $<'
	@echo ' '


