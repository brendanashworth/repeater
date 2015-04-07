CC ?= gcc
CC_FLAGS ?= -O3 -Wall

all:
	$(CC) $(CC_FLAGS) repeater.c -o repeater
