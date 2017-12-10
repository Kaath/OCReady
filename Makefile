CC=gcc

CPPFLAGS= `pkg-config --cflags sdl2` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O0 -g
LDFLAGS=
LDLIBS= -lm `pkg-config --libs sdl2` -lSDL2_image

OBJ= OCReady.o Reseau_de_Neuronne/operations.o Reseau_de_Neuronne/main.o Segmentation/main.o Segmentation/pixel_operations.o Segmentation/resize.o Segmentation/sdl_OP.o Segmentation/segmentation.o	Segmentation/Sobel.o
DEP= ${OBJ:.o=.d}

all: OCReady

OCReady: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} *~ *d OCReady

run:
	./OCReady ${ARGS}
	make clean

-include ${DEP}

# END
