# Makefile - makefile for our 'ones' driver

TARGET_MODULE := ones
BUILDSYSTEM_DIR := '/lib/modules/${shell uname -r}/build'
PWD := $(shell pwd)

obj-m := $(TARGET_MODULE).o

default: test
	${MAKE} -C ${BUILDSYSTEM_DIR} SUBDIRS=${PWD} modules

clean:
	${MAKE} -C ${BUILDSYSTEM_DIR} SUBDIRS=${PWD} clean
	rm -f test

test: test.c
	gcc -o test test.c
