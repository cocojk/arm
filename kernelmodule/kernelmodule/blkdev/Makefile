obj-m := blkdevicedriver.o
blkdevicedriverko-objs := blkdevicedriver.o
KDIR := /lib/modules/4.2.0-27-generic/build
PWD = $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.* .*.cmd
