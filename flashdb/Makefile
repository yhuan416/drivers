# 模块名
MODULE_NAME = flashdb

# 源文件
MODULE_OBJECTS += main.o

# 编译选项
EXTRA_CFLAGS += -DFDB_LKM -I$(PWD)
CFLAGS_main.o = -DDEBUG

# Toolchain Path
CROSS_COMPILE ?=
# Linux Kernel header
KERNEL ?= /lib/modules/$(shell uname -r)/build
# Architecture
ARCH := arm

FLASHDB_PATH := $(PWD)

PWD := $(shell pwd)

#enable logging by default
CONFIG_DEBUG_LOGS := y

obj-m := $(MODULE_NAME).o

# porting
EXTRA_CFLAGS += -I$(FLASHDB_PATH)/porting/inc
MODULE_OBJECTS += porting/src/fal_flash_lkm_port.o

# fal
# EXTRA_CFLAGS += -I$(FLASHDB_PATH)/FlashDB/port/fal/inc
MODULE_OBJECTS += FlashDB/port/fal/src/fal.o FlashDB/port/fal/src/fal_flash.o FlashDB/port/fal/src/fal_partition.o 

# flashdb
EXTRA_CFLAGS += -I$(FLASHDB_PATH)/FlashDB/inc
# MODULE_OBJECTS += FlashDB/src/fdb_file.o FlashDB/src/fdb_kvdb.o FlashDB/src/fdb_tsdb.o FlashDB/src/fdb_utils.o FlashDB/src/fdb.o
MODULE_OBJECTS += FlashDB/src/fdb_kvdb.o FlashDB/src/fdb_tsdb.o FlashDB/src/fdb_utils.o FlashDB/src/fdb.o

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
