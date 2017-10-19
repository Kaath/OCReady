#include "segmentation.h"
#include "pixel_operations.h"
#include "segmentation.h"
#include "Sobel.h"
#include "sdl_OP.h"

void binarisation(SDL_Surface* image) {
    for (int i = 0; i < image -> w; i++) {
        for (int j = 0; j < image -> h; j++) {
            Uint8 r,g,b;
            SDL_GetRGB(getpixel(image, i, j), image -> format, &r, &g, &b);
            float tot = (r * 0.3 + g * 0.59 + b * 0.11);
            tot = tot > 210 ? 255 : 0;
            putpixel(image, i, j, SDL_MapRGB(image -> format, tot, tot, tot));
        }
    }
}

/*SDL_Surface ***/void SurfaceSplit(SDL_Surface *img, int histo[]) {//, int *ref) {

    for (int i = 0; i < img->h; i++) {
        if (histo[i] != -1){
            int begin = i;
            i++;
            while (i < img -> h && histo[i] != -1) { i++; }
            int end = i;
            SDL_Rect src = {0, begin, img->w, end - begin};
            SDL_Surface *screen = SDL_SetVideoMode(img->w, end - begin, 0, SDL_SWSURFACE|SDL_ANYFORMAT|SDL_DOUBLEBUF);
            SDL_BlitSurface(img, &src, screen, NULL);
            SDL_UpdateRect(screen, 0, 0, img->w, end - begin);
            wait_for_keypressed();
        }

        else {
            i++;
        }
    }
}

int *HistoHorizontal(SDL_Surface *image) {

    int *histo = malloc(image -> h * sizeof(int));
    for (int i = 0; i < image -> h; i++) {
        int mid = 0, j;
        for (j = 0; j < image -> w; j++) {
            Uint8 r,g,b;
            SDL_GetRGB(getpixel(image, j, i), image -> format, &r, &g, &b);
            mid += r;
        }
        histo[i] = mid / j < 253 ? mid / j : -1;
    }

    return histo;
}

int *HistoVertical(SDL_Surface *image) {

    int *histo = malloc(image -> h * sizeof(int));
    for (int i = 0; i < image -> h; i++) {
        int mid = 0, j;
        for (j = 0; j < image -> w; j++) {
            Uint8 r,g,b;
            SDL_GetRGB(getpixel(image, j, i), image -> format, &r, &g, &b);
            mid += r;
        }
        histo[i] = mid / j < 253 ? mid / j : -1;
    }

    return histo;
}
