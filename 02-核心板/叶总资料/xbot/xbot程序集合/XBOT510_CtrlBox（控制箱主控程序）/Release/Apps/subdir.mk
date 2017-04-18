################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Apps/AdcControl.c \
../Apps/Debug.c \
../Apps/RelayCtrl.c \
../Apps/SystemInit.c \
../Apps/TcInit.c \
../Apps/UsartInit.c 

OBJS += \
./Apps/AdcControl.o \
./Apps/Debug.o \
./Apps/RelayCtrl.o \
./Apps/SystemInit.o \
./Apps/TcInit.o \
./Apps/UsartInit.o 

C_DEPS += \
./Apps/AdcControl.d \
./Apps/Debug.d \
./Apps/RelayCtrl.d \
./Apps/SystemInit.d \
./Apps/TcInit.d \
./Apps/UsartInit.d 


# Each subdirectory must supply rules for building sources it contributes
Apps/%.o: ../Apps/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"F:\程序实例\叶依顺2013年工作备份\机器人本体程序(修改)\XBOT510_CtrlBox\Includes" -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -mmcu=atxmega64a3 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


