obj-m += gpio_driver.o
# KERNELDIR ?= /usr/src/linux-headers-6.6.34-v8+
KERNELDIR ?= /usr/src/linux  # 源碼編譯的目錄

PWD := $(shell pwd)

# Add standard include paths
# EXTRA_CFLAGS += -I/usr/include
# EXTRA_CFLAGS += -I/usr/linux/include -I/usr/src/linux-headers-6.6.34-v8+/include 

all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
