################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/TC_driver.c \
../Drivers/adc_driver.c \
../Drivers/clksys_driver.c \
../Drivers/eeprom_driver.c \
../Drivers/pmic_driver.c \
../Drivers/port_driver.c \
../Drivers/usart_driver.c 

OBJS += \
./Drivers/TC_driver.o \
./Drivers/adc_driver.o \
./Drivers/clksys_driver.o \
./Drivers/eeprom_driver.o \
./Drivers/pmic_driver.o \
./Drivers/port_driver.o \
./Drivers/usart_driver.o 

C_DEPS += \
./Drivers/TC_driver.d \
./Drivers/adc_driver.d \
./Drivers/clksys_driver.d \
./Drivers/eeprom_driver.d \
./Drivers/pmic_driver.d \
./Drivers/port_driver.d \
./Drivers/usart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o: ../Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"E:\项目管理\7.XBOT_UPTECH项目管理\10.板子程序\机器人本体程序20130115(加水炮)\XBOT510_CtrlBox\Includes" -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -mmcu=atxmega64a3 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


