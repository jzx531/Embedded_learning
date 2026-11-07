ARCH=x86
CROSS_COMPILE=

KVERSION = $(shell uname -r)
# KERN_DIR =  /lib/modules/$(KVERSION)/build 
KERN_DIR=/home/jzx/WSL2-Linux-Kernel

all:
	make -C $(KERN_DIR) M=`pwd` modules 

clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -rf modules.order

obj-m	+= hello_drv.o
obj-m	+= hello_dev.o

# make KERN_DIR=/home/jzx/WSL2-Linux-Kernel