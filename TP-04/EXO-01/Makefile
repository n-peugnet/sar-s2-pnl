KERNELDIR_PNL ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += helloWorld.o

all :
	make -C $(KERNELDIR_PNL) M=$(PWD) modules

clean:
	make -C $(KERNELDIR_PNL) M=$(PWD) clean

