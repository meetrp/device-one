# 
# Copyright 2013 Rp (www.meetrp.com)
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#       http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 

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
