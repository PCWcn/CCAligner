# This Makefile requires GNU make.
SHELL = /bin/sh
CC = g++
LEX = flex
PROGRAM = c1c
BIN = bin
SRC = src
INC = src/include
CONF = src/config
CFLAGS = -I ${INC}
LFLAGS =
YFLAGS =

default:: ${BIN}/c1c

${BIN}/c1c: ${BIN}/lexer.o ${BIN}/main.o ${BIN}/tok.o
	mkdir -p ${BIN}
	${CC} ${CFLAGS} -o $@ $^

${SRC}/lexer.cpp: ${CONF}/lexer.l
	mkdir -p ${SRC}
	${LEX} ${LFLAGS} -o $@ $<

${BIN}/lexer.o: ${SRC}/lexer.cpp ${INC}/tok.h
	mkdir -p ${SRC}
	${CC} ${CFLAGS} -c -o $@ $<

${BIN}/tok.o: ${SRC}/tok.cpp
	mkdir -p ${SRC}
	${CC} ${CFLAGS} -c -o $@ $<

${BIN}/main.o: ${SRC}/main.cpp
	mkdir -p ${SRC}
	${CC} ${CFLAGS} -c -o $@ $<

.PHONY: clean
clean:
	-rm -f ${BIN}/*.o ${SRC}/lexer.cpp
