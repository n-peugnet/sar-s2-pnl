obj-m += helloioctl.o

KERNELDIR_PNL ?= ../../linux
PWD := $(shell pwd)

all: hello_user
	$(info obj-m : $(obj-m))
	make -C $(KERNELDIR_PNL) M=$(PWD) modules

clean:
	make -C $(KERNELDIR_PNL) M=$(PWD) clean

mknod:
	mknod /dev/hello c $(MAJOR) 0

rmnod:
	rm /dev/hello

hello_user: hello_user.o
	gcc $^ -o $@

%.o: %.c
	gcc -c $< -o $@