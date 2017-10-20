#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

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
    display_image(image);

    binarisation(image);
    display_image(image);

    Sobel(image);
    display_image(image);


    int *hist = HistoMake(image, 0);
    for (int i = 0; i < image -> h; i++) {
        printf("%d\n", hist[i]);
    }

    //SurfaceSplit(image, hist);
    SDL_Surface **lignes = SurfaceSplit(image, hist, &nblignes);

    for (int i = 0; i < nblignes; i++) {
        display_image(lignes[i]);
    }

    SDL_FreeSurface(image);
    free(lignes);
    return 0;

}
