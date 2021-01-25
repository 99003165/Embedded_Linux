obj-m += dummy_serial.o
#KSRC=/home/bltsl02527/eworkdir/elinux/kernel_ws/linux-4.14.199
KSRC=/lib/modules/$(shell uname -r)/build	
#replace KSRC if building for other kernel version
all:
	make -C ${KSRC} M=${PWD} modules #ARCH=arm #CROSS_COMPILE=arm-linux-gnueabi-
clean:
	make -C ${KSRC} M=${PWD} clean #ARCH=arm #CROSS_COMPILE=arm-linux-gnueabi-
