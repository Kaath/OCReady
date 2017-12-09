#include "main.h"

float *implem(SDL_Surface *img) {
    float *ret = malloc(img->w * img->h * sizeof(float));
    for (int i = 0; i < img->h; i++) {
        for (int j = 0; j < img->w; j++) {
            Uint8 r,g,b;
            SDL_GetRGB(getpixel(img, i, j), img -> format, &r, &g, &b);
            ret[i] = r != (float)0 ? 1 : 0;
            printf("%f\n", ret[i]);
        }
    }
    return ret;
}

float **convert(SDL_Surface **imgs, size_t len) {
    float **ret = malloc(len * sizeof(float*));
    for (size_t i = 0; i < len; i++) {
        ret[i] = implem(imgs[i]);
    }
    return ret;
}

float **decoupe(char *path) {
    int nblignes;

    init_sdl();
    SDL_Surface* image = LoadImage(path);
    SDL_Window *win = SDL_CreateWindow("OCReady", 0, 0, image->w, image->h, SDL_SWSURFACE);
    display_image(win,image);

    binarisation(image);
    display_image(win,image);

    //Sobel(image);
    //display_image(win,image);


    int *hist = HistoMake(image, 0);

    /*
    for (int i = 0; i < image -> h; i++) {
        printf("%d\n", hist[i]);
    }
    */

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

    float **mat = convert(characters, nblignes);

    SDL_FreeSurface(image);
    for (int i = 0; i < nblignes; i++) {
        SDL_FreeSurface(characters[i]);
    }
    free(characters);
    return mat;
}
