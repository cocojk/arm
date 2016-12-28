CC := gcc
obj-m := 1.test_module.o
KDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.* .*.cmd
