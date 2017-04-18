###############################################################################
# Makefile for the project CbBoxDebug
###############################################################################

## General Flags
PROJECT = CbBoxDebug
MCU = atxmega64a3
TARGET = CbBoxDebug.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -O0 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=CbBoxDebug.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"E:\XmegaSoft\XBOT510_CtrlBox\Includes" 

## Objects that must be built in order to link
OBJECTS = CbBoxDebug.o AdcControl.o Debug.o RelayCtrl.o SystemInit.o TcInit.o UsartInit.o adc_driver.o clksys_driver.o eeprom_driver.o pmic_driver.o port_driver.o TC_driver.o usart_driver.o CbCtrl.o CbCtrlData.o CbDisCtrl.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) CbBoxDebug.hex CbBoxDebug.eep CbBoxDebug.lss size

## Compile
CbBoxDebug.o: ../CbBoxDebug.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

AdcControl.o: ../Apps/AdcControl.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Debug.o: ../Apps/Debug.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

RelayCtrl.o: ../Apps/RelayCtrl.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

SystemInit.o: ../Apps/SystemInit.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

TcInit.o: ../Apps/TcInit.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

UsartInit.o: ../Apps/UsartInit.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

adc_driver.o: ../Drivers/adc_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

clksys_driver.o: ../Drivers/clksys_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

eeprom_driver.o: ../Drivers/eeprom_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

pmic_driver.o: ../Drivers/pmic_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port_driver.o: ../Drivers/port_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

TC_driver.o: ../Drivers/TC_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

usart_driver.o: ../Drivers/usart_driver.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

CbCtrl.o: ../Protocol/CbCtrl.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

CbCtrlData.o: ../Protocol/CbCtrlData.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

CbDisCtrl.o: ../Protocol/CbDisCtrl.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) CbBoxDebug.elf dep/* CbBoxDebug.hex CbBoxDebug.eep CbBoxDebug.lss CbBoxDebug.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

