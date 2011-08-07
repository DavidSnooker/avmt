CROSS_COMPILE = arm-none-linux-gnueabi-
KERNEL = ../qemu/
ARCH = arm

obj-m += avmt_server.o

all:
	$(MAKE) -C $(KERNEL) M=$(PWD) modules 
clean:
	$(MAKE) -C $(KERNEL) M=$(PWD) clean
