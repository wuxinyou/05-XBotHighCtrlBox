################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Protocol/CbCtrl.c \
../Protocol/CbCtrlData.c \
../Protocol/CbDisCtrl.c 

OBJS += \
./Protocol/CbCtrl.o \
./Protocol/CbCtrlData.o \
./Protocol/CbDisCtrl.o 

C_DEPS += \
./Protocol/CbCtrl.d \
./Protocol/CbCtrlData.d \
./Protocol/CbDisCtrl.d 


# Each subdirectory must supply rules for building sources it contributes
Protocol/%.o: ../Protocol/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"F:\程序实例\叶依顺2013年工作备份\机器人本体程序(修改)\XBOT510_CtrlBox\Includes" -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -mmcu=atxmega64a3 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


