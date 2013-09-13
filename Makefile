# Makefile - makefile for our 'one' driver

TARGET_MODULE := one

# if KERNELRELEASE is defined, we have been invoked from the
# kernel build system
ifneq (${KERNELRELEASE},)
	$(TARGET_MODULE)-objs := ones.o
	obj-m := $(TARGET_MODULE).o
# if not then we were called directly from the cmd-line.
# Invoke the kernel build system
else
	BUILDSYSTEM_DIR := '/lib/modules/${shell uname -r}/build'
	PWD := $(shell pwd)
default: test
	${MAKE} -C ${BUILDSYSTEM_DIR} SUBDIRS=${PWD} modules

clean:
	${MAKE} -C ${BUILDSYSTEM_DIR} SUBDIRS=${PWD} clean
	rm -f test

test: test.c
	gcc -o test test.c
endif
