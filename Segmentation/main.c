#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "resize.h"
#include "pixel_operations.h"
#include "segmentation.h"
#include "Sobel.h"
#include "sdl_OP.h"



int main(int argc, const char *argv[]) {
    if (argc < 2) {
        errx(1,"%s", "wrong usage");
    }

    int nblignes;

    init_sdl();
    SDL_Surface* image = LoadImage(argv[1]);
    SDL_Window *win = SDL_CreateWindow("OCReady", 0, 0, image->w, image->h, SDL_SWSURFACE);
    display_image(win,image);

    binarisation(image);
    display_image(win,image);

    Sobel(image);
    display_image(win,image);


    int *hist = HistoMake(image, 0);
    for (int i = 0; i < image -> h; i++) {
        printf("%d\n", hist[i]);
    }

    SDL_Surface **lignes = SurfaceSplit(image, hist, &nblignes);

    /*for (int i = 0; i < nblignes; i++) {
        display_image(lignes[i]);
    }*/

    int *histChar[nblignes];

    for (int i = 0; i < nblignes; i++) {
        histChar[i] = HistoMake(lignes[i], 1);
    }

    SDL_Surface **characters = characterSplit(lignes, histChar, &nblignes);

    for (int i = 0; i < nblignes; i++) {
        display_image(win, characters[i]);
    }

    SDL_FreeSurface(image);
    free(lignes);
    return 0;

}
