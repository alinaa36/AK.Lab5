ifneq ($(KERNELRELEASE),)
# kbuild part of makefile
obj-m := hello1.o 
obj-m := hello2.o
ccflags-y := -I$(src)/inc
else
# normal makefile
KDIR ?= /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KDIR) M=$(PWD)

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
endif
