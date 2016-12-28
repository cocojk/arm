obj-m := moduleko.o
moduleko-objs := mymodule.o other_file.o

KERNEL:= /lib/modules/4.2.0-27-generic/build

PWD:=$(shell pwd)

all:
	$(MAKE) -C $(KERNEL) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL) M=$(PWD) clean
