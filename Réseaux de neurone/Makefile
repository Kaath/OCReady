## Simple SDL mini code

CC=gcc

CPPFLAGS=  -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3
LDFLAGS=
LDLIBS= -lm

OBJ= operations.o main.o
DEP= ${OBJ:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~ *d
	${RM} main

run:
	./main ${ARGS}
	make clean

-include ${DEP}

# END
