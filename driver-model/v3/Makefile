obj-m += dummy_serial.o

KSRC=/home/user/EmbeddedLinux/KSRC
ARCH=arm
CROSS_COMPILE_PREFIX=arm-linux-gnueabi-

all:
	make -C ${KSRC} M=${PWD} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE_PREFIX} modules
clean:
	make -C ${KSRC} M=${PWD} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE_PREFIX} clean
