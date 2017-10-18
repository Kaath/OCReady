#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

#include "pixel_operations.h"

void wait_for_keypressed(void) {
    SDL_Event event;
    for (;;) {
        SDL_PollEvent( &event );

        switch (event.type) {

            case SDL_KEYDOWN: return;

            default: break;
        }
    }
}

void init_sdl(void) {
    if(SDL_Init(SDL_INIT_VIDEO) ==- 1) {
        errx(1, "Could not initialize SDL: %s.\n", SDL_GetError());
    }
}

SDL_Surface* LoadImage(const char *path) {
    SDL_Surface *img;
    img = IMG_Load(path);
    if(!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());
    return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT|SDL_DOUBLEBUF);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // wait for a key
  wait_for_keypressed();

  // return the screen for further uses
  return screen;
}

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
            SDL_GetRGB(getpixel(image, i, j), image -> format, &r, &g, &b);
            mid += r;
        }
        histo[i] = mid / j > 253 ? mid / j : -1;
    }

    return histo;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        errx(1,"%s", "wrong usage");
    }

    //int nblignes;

    init_sdl();
    SDL_Surface* image = LoadImage(argv[1]);
    display_image(image);

    binarisation(image);
    display_image(image);

    int *hist = HistoHorizontal(image);
    for (int i = 0; i < image -> h; i++) {
        printf("%d\n", hist[i]);
    }

    SurfaceSplit(image, hist);
    /*SDL_Surface **lignes = SurfaceSplit(image, HistoHorizontal(image), &nblignes);

    for (int i = 0; i < nblignes; i++) {
        display_image(lignes[i]);
    }
    */
    SDL_FreeSurface(image);
    return 0;

}
