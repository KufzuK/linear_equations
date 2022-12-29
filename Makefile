CFLAGS = -Wall -Wextra -Werror
INCLUDE_DIR = ./include
SRC_DIR = src/
BUILD_DIR = build/
TESTS_DIR = tests/
CC = gcc


all:
	@echo 'probably.., compiling' 
	@${CC} -g ${CFLAGS} ${SRC_DIR}systems.c -I ${INCLUDE_DIR} ${TESTS_DIR}main.c -lm -o ${BUILD_DIR}/solve
