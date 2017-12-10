#include "segmentation.h"

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

SDL_Surface **SurfaceSplit(SDL_Surface *img, int histo[], int *ref) {
    SDL_Surface *imgs[img -> h];
    int count = 0;
    for (int i = 0; i < img->h; i++) {
        if (histo[i] != -1){
            int begin = i;
            i++;
            while (i < img -> h && histo[i] != -1) { i++; }
            int end = i;
            SDL_Rect src = {0, begin, img->w, end - begin};
            SDL_Surface *screen = SDL_CreateRGBSurface(0, img->w, end - begin, 32, 0, 0, 0, 0);
            SDL_BlitSurface(img, &src, screen, NULL);
            //SDL_UpdateRect(screen, 0, 0, img->w, end - begin);
            imgs[count] = screen;
            count++;
            //wait_for_keypressed();
            SDL_Surface *rc = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
            imgs[count] = rc;
            count++;
        }

        else {
            i++;
        }
    }

    *ref = count;
    SDL_Surface **surfs = malloc(count * sizeof(SDL_Surface*));
    for (int i = 0; i < count; i++) {
        surfs[i] = imgs[i];
    }

    return surfs;
}

SDL_Surface **characterSplit(SDL_Surface *img[], int *histo[], int *ref) {
    SDL_Surface *imgs[*ref * (img[0] -> w)];
    int lastchar = 0;
    int count = 0;
    for (int i = 0; i < *ref; i++) {
        SDL_Surface *s = img[i];
        if(s->w == 1 && s->h == 1) {
            imgs[count] = s;
            count++;
        }
        else {
            int *h = histo[i];
            for (int j = 0; j < s -> w; j++) {
                if (h[j] != -1) {
                    int begin = j;
                    j++;
                    while (j < s -> w && h[j] != -1) { j++; }
                    int end = j;
                    SDL_Rect src = {begin, 0, end - begin, s -> h};
                    //SDL_Surface *screen = SDL_CreateRGBSurface(0, end - begin, s -> h, 32, 0, 0, 0, 0);
                    //SDL_BlitSurface(s, &src, screen, NULL);
                    SDL_Surface *ret = resize(s, src, 28, 28);
                    imgs[count] = ret;
                    count++;
                    if (lastchar == 0) {lastchar = end;}
                    else if (end - lastchar > 15) {
                        SDL_Surface *res = SDL_CreateRGBSurface(0, 2, 2, 32, 0, 0, 0, 0);
                        imgs[count] = res;
                        count++;
                        lastchar = end;
                    }
                }

                else {
                    j++;
                }
            }
        }
    }

    *ref = count;
    SDL_Surface **characters = malloc(count * sizeof(SDL_Surface*));
    for (int i = 0; i < count; i++) {
        characters[i] = imgs[i];
    }

    return characters;
}

int *HistoMake(SDL_Surface *image, int vert) {

    int H;
    int W;
    int Hbool;
    int Vbool;

    if (vert == 0) {
        H = image -> h;
        W = image -> w;
        Hbool = 1;
        Vbool = 0;
    }

    else {
        H = image -> w;
        W = image -> h;
        Hbool = 0;
        Vbool = 1;
    }

    int *histo = malloc(H * sizeof(int));
    for (int i = 0; i < H; i++) {
        int mid = 0, j;
        for (j = 0; j < W; j++) {
            Uint8 r,g,b;
            SDL_GetRGB(getpixel(image, j*Hbool + i*Vbool, i*Hbool + j*Vbool), image -> format, &r, &g, &b);
            mid += r;
        }
        histo[i] = mid / j < 253 ? mid / j : -1;
    }

    return histo;
}
/*
char implem(SDL_Surface *img) {
    float tab[img->w*img->h];
    float *pix = img->pixels;
    for (int i = 0; i < img->w * img->h; i++) {
        tab[i] = pix[i] / 255;
    }
    return result(tab);
}*/
