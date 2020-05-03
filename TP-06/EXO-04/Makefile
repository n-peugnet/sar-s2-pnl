obj-m += taskmonitor.o

KERNELDIR_PNL ?= ../../linux
ccflags-y += -g -DDEBUG
CC += $(CFLAGS)
PWD := $(shell pwd)

all :
	$(info obj-m : $(obj-m))
	make -C $(KERNELDIR_PNL) M=$(PWD) modules

clean:
	make -C $(KERNELDIR_PNL) M=$(PWD) clean
