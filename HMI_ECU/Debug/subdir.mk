################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Keypad.c \
../LCD.c \
../Timer.c \
../gpio.c \
../lala.c \
../main.c \
../uart.c 

OBJS += \
./Keypad.o \
./LCD.o \
./Timer.o \
./gpio.o \
./lala.o \
./main.o \
./uart.o 

C_DEPS += \
./Keypad.d \
./LCD.d \
./Timer.d \
./gpio.d \
./lala.d \
./main.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


