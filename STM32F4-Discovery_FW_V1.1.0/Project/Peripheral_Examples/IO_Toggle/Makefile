# Put your stlink folder here so make burn will work.
STLINK=/usr/local/bin/

SRCS=main.c system_stm32f4xx.c stm32f4xx_it.c

# Library modules
SRCS += stm32f4xx_gpio.c stm32f4xx_rcc.c

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=io_toggle

# location of OpenOCD Board .cfg files (only used with 'make program')
OPENOCD_BOARD_DIR=/usr/local/share/openocd/scripts/board

STM_COMMON=$(HOME)/openstm32f407xx/STM32F4-Discovery_FW_V1.1.0

#######################################################################################
CC=arm-none-eabi-gcc
GDB=arm-none-eabi-gdb
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld 
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.

# Include files from STM libraries
CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include 
CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc


# add startup file to build
SRCS += $(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TrueSTUDIO/startup_stm32f4xx.s 

OBJS = $(SRCS:.c=.o)

vpath %.c $(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/src

.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ 
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

## Flashing boards using OpenOCD
flash_openocd:
	openocd -f $(OPENOCD_BOARD_DIR)/stm32f4discovery.cfg -c "program $(PROJ_NAME).bin exit 0x8000000"

# Flashing boards using STLink
flash_stlink:
	st-flash write $(PROJ_NAME).bin 0x8000000

clean:
	find ./ -name '*~' | xargs rm -f	
	rm -f $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin *.o

reallyclean: clean
	$(MAKE) -C $(STD_PERIPH_LIB) clean

# Debugger GDB
debug:
	$(GDB) $(PROJ_NAME).elf

# Start OpenOCD GDB server (supports semihosting)
openocd: 
	openocd -f $(OPENOCD_BOARD_DIR)/stm32f4discovery.cfg
