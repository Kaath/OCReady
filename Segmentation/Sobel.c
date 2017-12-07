#include "Sobel.h"

int* SobelH(SDL_Surface* img) {

    int *hist = malloc((img -> w * img -> h) * sizeof(int));
    for (int i = 0; i < img->h; ++i)
    {
        for (int j = 0; j < img->w-1; ++j)
        {
            if (getpixel(img, j, i) != getpixel(img, j + 1, i))
            {
                hist[j + i*img->w] = 1;
            }
        }
    }
    return hist;
}

int* SobelV(SDL_Surface* img) {

    int *hist = malloc((img -> w * img -> h) * sizeof(int));
    for (int j = 0; j < img->w; ++j)
    {
        for (int i = 0; i < img->h-1; ++i)
        {
            if (getpixel(img, j, i) != getpixel(img, j, i + 1))
            {
                hist[j + i*img->w] = 1;
            }
        }
    }
    return hist;
}

SDL_Surface* Sobel(SDL_Surface* img)
{
    int *hori = SobelH(img);
    int *vert = SobelV(img);
    for (int i = 0; i<img->h; ++i)
    {
        for (int j = 0; j<img->w; ++j)
        {
            if (hori[j +i * img->w] == 1 || vert[j + i * img->w] == 1)
            {
                putpixel(img, j, i, SDL_MapRGB(img->format,0,0,0));
            }
            else
            {
                putpixel(img, j, i, SDL_MapRGB(img->format,255,255,255));
            }
        }
    }
    free(hori);
    free(vert);
    return img;
}
