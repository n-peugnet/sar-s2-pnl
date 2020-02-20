# KERNELDIR_PNL ?= /lib/modules/$(shell uname -r)/build
KERNELDIR_PNL ?= ../linux
PWD := $(shell pwd)

obj-m += helloWorld.o helloWorldParam.o

all :
	make -C $(KERNELDIR_PNL) M=$(PWD) modules

clean:
	make -C $(KERNELDIR_PNL) M=$(PWD) clean

