#
#	Universidade Lusofona  - LP1 2018/2019
#
#	Guilherme Sanches - P5652
# v1.1

CC=gcc
CFLAGS= -ansi -Wall -Wpedantic -Wextra -Iinclude

EXE_SRC_FILES=$(wildcard *.c)
SRC_FILES=$(wildcard src/*.c)
H_FILES=$(wildcard include/*.h)
O_FILES=$(patsubst src/%.c, build/%.o, $(SRC_FILES))

all: 
	$(CC) $(CFLAGS) $(SRC_FILES) -o trotify -lm
	
debug:
	$(CC) -g $(CFLAGS) $(SRC_FILES) -o trotify -lm

.PHONY: clean

clean:
	rm -rf trotify
