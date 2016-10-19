################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BowlingScoreKeeper.cpp \
../src/bsk1.cpp \
../src/bsk2.cpp \
../src/bsk3.cpp \
../src/bsk4.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc8xx.cpp \
../src/delay.cpp \
../src/display.cpp \
../src/i2c.cpp \
../src/swm.cpp 

C_SRCS += \
../src/crp.c \
../src/mtb.c \
../src/sysinit.c 

OBJS += \
./src/BowlingScoreKeeper.o \
./src/bsk1.o \
./src/bsk2.o \
./src/bsk3.o \
./src/bsk4.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc8xx.o \
./src/crp.o \
./src/delay.o \
./src/display.o \
./src/i2c.o \
./src/mtb.o \
./src/swm.o \
./src/sysinit.o 

CPP_DEPS += \
./src/BowlingScoreKeeper.d \
./src/bsk1.d \
./src/bsk2.d \
./src/bsk3.d \
./src/bsk4.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc8xx.d \
./src/delay.d \
./src/display.d \
./src/i2c.d \
./src/swm.d 

C_DEPS += \
./src/crp.d \
./src/mtb.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DNDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_LPCOPEN -DNO_BOARD_LIB -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM0 -DCPP_USE_HEAP -D__LPC8XX__ -I"/home/student/git/SQAT_embedded_test_BSK/inc" -Os -fno-common -Os -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DNDEBUG -D__CODE_RED -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_LPCOPEN -DNO_BOARD_LIB -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM0 -DCPP_USE_HEAP -D__LPC8XX__ -I"/home/student/git/SQAT_embedded_test_BSK/inc" -Os -fno-common -g -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


