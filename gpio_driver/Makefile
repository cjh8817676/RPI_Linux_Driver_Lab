obj-m += gpio_driver.o
# KERNEL_BUILD is less commonly used but can be defined to specify the directory where the kernel is actually built.
# KERNEL_BUILD := /usr/src/linux
# KERNELDIR is commonly used to specify the path to the directory where the kernel headers and build scripts are located.
# KERNELDIR ?= /usr/src/linux-headers-6.6.34-v8+
KERNELDIR ?= /usr/src/linux

PWD := $(shell pwd)

# Add standard include paths
# EXTRA_CFLAGS += -I/usr/include
EXTRA_CFLAGS += -I/usr/src/linux-headers-6.6.34-v8+/include -I/usr/src/linux/include -I/usr/include


all:
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
