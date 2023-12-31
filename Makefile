SRC = dll-test.c
CC = cc
LIBS =
CFLAGS = -x c -O3 -pedantic -Wall -Wextra -std=c11 -ggdb

all: options dll

options:
	@echo dll build options:
	@echo "CFLAGS = ${CFLAGS}"
	@echo "LIBS   = ${LIBS}"
	@echo "CC     = ${CC}"

dll:
	${CC} -DDLL_IMPLEMENTATION ${CFLAGS} ${LIBS} -c dll.h

test:
	${CC} -o $@ ${SRC} ${CFLAGS} ${LIBS}
	./$@

clean:
	rm -f dll.o test

.PHONY: all clean options test
