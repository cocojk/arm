CROSS = ~/arm/arm_emultator_2.6/output/host/usr/bin/arm-buildroot-linux-musleabi-
obj-m := jprobe_udp.o 
kojprobe-objs := jprobe_udp.o
KDIR := ~/arm/arm_emultator_2.6/output/build/linux-custom
PWD = $(shell pwd)

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.* .*.cmd
