# sam9x75_chip_id

Export the CHIP ID and the Extended ID register of the Microchip SAM9x75 into the sysfs.

Steps:

Export the ARCH & CROSS_COMPILE environment variables to "arm" and "arm-linux-gnueabi-" respectively.
 
make KDIR=<path to kernel source compiled for sam9x75>
 
The driver module "chip_id.ko" will be generated locally which can be transferred to the target and loaded using 'insmod' command.
 
We can then query the chip ID and the extended ID register as below from the command line.
 
root@sam9x75-curiosity-sd:/# cat  /sys/kernel/chip_info/chip_id 
Chip ID: 0x89750030, Extended ID: 0x20
