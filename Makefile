CFLAGS = -Wall -Wextra -Werror
INCLUDE_DIR = ./include
SRC_DIR = src/
BUILD_DIR = build/
TESTS_DIR = tests/
CC = gcc
CRAMER = -D Cramer
SRC = systems.c
MAIN = main.c
TESTS = tests.c


all:
	@echo 'probably.., compiling' 
	@${CC} -g ${CFLAGS} ${SRC_DIR}${SRC} ${SRC_DIR}${TESTS} -I ${INCLUDE_DIR} ${TESTS_DIR}${MAIN} -lm -o ${BUILD_DIR}/solve
