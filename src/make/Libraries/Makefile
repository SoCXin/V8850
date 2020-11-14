CPU = MM32L073

CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar

###########################################

vpath %.c CMSIS/Device/MindMotion/Source MM32L0xx_StdPeriph_Driver/src

CFLAGS  = -g -O2 -Wall -D$(CPU)
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m0 -march=armv6s-m
CFLAGS += -ffreestanding -nostdlib
CFLAGS += -ICMSIS/Include -ICMSIS/Device/MindMotion/Include -IMM32L0xx_StdPeriph_Driver/inc

SRCS  = system_MM32L073.c
SRCS += HAL_adc.c HAL_dma.c HAL_exti.c HAL_flash.c \
	   HAL_gpio.c HAL_i2c.c HAL_iwdg.c HAL_misc.c \
	   HAL_pwr.c HAL_rcc.c HAL_spi.c HAL_syscfg.c \
	   HAL_tim.c HAL_uart.c HAL_wwdg.c HAL_can.c

OBJS = $(SRCS:.c=.o)

.PHONY: libmm32l0.a

all: libmm32l0.a

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

libmm32l0.a: $(OBJS)
	$(AR) -r $@ $(OBJS)

clean:
	rm -f $(OBJS) libmm320.a

