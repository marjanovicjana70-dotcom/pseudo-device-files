

ifeq ($(KERNELRELEASE),)

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)


.PHONY: modules modules_install clean


all: modules


modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules


modules_install: 
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install


clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.mod modules.order *.symvers .*.o

else

obj-m := byteDump.o

endif