# Name of the module
obj-m += chip_id.o

# Path to the kernel headers
KDIR := /lib/modules/$(shell uname -r)/build

# Default target
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Clean up
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
