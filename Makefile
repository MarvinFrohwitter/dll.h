SRC = dll-test.c
OBJ = ${SRC:.c=.o}

CC = cc
LIBS =
CFLAGS = -O3 -pedantic -Wall -Wextra -std=c11 -ggdb

all: options dll

options:
	@echo dll build options:
	@echo "CFLAGS = ${CFLAGS}"
	@echo "LIBS   = ${LIBS}"
	@echo "CC     = ${CC}"

dll:
	${CC} -o $@ ${SRC} ${CFLAGS} ${LIBS}

test:
	${CC} -o $@ ${SRC} ${CFLAGS} ${LIBS}
	./$@

clean:
	rm -f dll

.PHONY: all clean options test
