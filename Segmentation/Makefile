## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl2` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O0
LDFLAGS=
LDLIBS= `pkg-config --libs sdl2` -lSDL2_image

OBJ= main.o pixel_operations.o resize.o sdl_OP.o segmentation.o	Sobel.o
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
