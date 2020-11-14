CPU = MM32L073

# put your *.o targets here, make should handle the rest!
SRCS  = main.c 
SRCS += delay.c
SRCS += led.c
SRCS += uart.c

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)
PROJ_NAME=MM32L073_TEST

# Location of the Libraries folder from the MM32L0xx Standard Peripheral Library
STD_PERIPH_LIB=Libraries

# Location of the linker scripts
LDSCRIPT_INC=Device/ldscripts

# that's it, no need to change anything below this line!

###################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
SIZE=arm-none-eabi-size

DEFS = -D$(CPU)

CFLAGS  = -Wall -g -std=c99 -Os  
#CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m0 -march=armv6s-m
CFLAGS += -mlittle-endian -mcpu=cortex-m0  -march=armv6-m -mthumb
CFLAGS += -ffunction-sections -fdata-sections
CFLAGS += -Wl,--gc-sections -Wl,-Map=$(PROJ_NAME).map $(DEFS)

###################################################

vpath %.c src
vpath %.a $(STD_PERIPH_LIB)

ROOT=$(shell pwd)

CFLAGS += -I inc -I $(STD_PERIPH_LIB) -I $(STD_PERIPH_LIB)/CMSIS/Device/MindMotion/Include
CFLAGS += -I $(STD_PERIPH_LIB)/CMSIS/Include -I $(STD_PERIPH_LIB)/MM32L0xx_StdPeriph_Driver/inc

ifeq ($(CPU), MM32L073)
SRCS += $(STD_PERIPH_LIB)/CMSIS/Device/MindMotion/Source/startup_MM32L073.s # add startup file to build
endif

OBJS = $(SRCS:.c=.o)

###################################################

.PHONY: lib proj

all: lib proj

lib:
	$(MAKE) -C $(STD_PERIPH_LIB)

proj: 	$(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(STD_PERIPH_LIB) -lmm32l0 -L$(LDSCRIPT_INC) -Tmm32l0.ld
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(OBJDUMP) -St $(PROJ_NAME).elf >$(PROJ_NAME).lst
	$(SIZE) $(PROJ_NAME).elf
	
clean:
	find ./ -name '*~' | xargs rm -f	
	rm -f *.o
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).map
	rm -f $(PROJ_NAME).lst
	rm -f src/*.bak

reallyclean: clean
	$(MAKE) -C $(STD_PERIPH_LIB) clean
