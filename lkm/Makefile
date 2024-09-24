# 模块名
MODULE_NAME = lkm

# 源文件
MODULE_OBJECTS += main.o

# 编译选项
EXTRA_CFLAGS += -I$(PWD)
CFLAGS_main.o = -DDEBUG

# Toolchain Path
CROSS_COMPILE ?=
# Linux Kernel header
KERNEL ?= /lib/modules/$(shell uname -r)/build
# Architecture
ARCH := arm

PWD := $(shell pwd)

#enable logging by default
CONFIG_DEBUG_LOGS := y

obj-m := $(MODULE_NAME).o

$(MODULE_NAME)-y := $(MODULE_OBJECTS)

.PHONY: clean info

all: clean
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL) M=$(PWD) modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERNEL) M=$(PWD) clean

info:
	@echo "KERNEL=$(KERNEL)"
	@echo "MODULE_NAME=$(MODULE_NAME)"
	@echo "SRC=$(MODULE_OBJECTS)"
	@echo "PWD=$(PWD)"
