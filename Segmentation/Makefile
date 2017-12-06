## Simple SDL mini   code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lSDL_gfx

OBJ= pixel_operations.o main.o segmentation.o Sobel.o sdl_OP.o resize.o
DEP= ${OBJ:.o=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~ *d
	${RM} main

run:
	gdb -q --args ./main ${ARGS}
	make clean

-include ${DEP}

# END
