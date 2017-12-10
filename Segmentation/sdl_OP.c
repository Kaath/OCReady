#include "sdl_OP.h"

/*
void wait_for_keypressed(void) {
    SDL_Event event;
    for (;;) {
        SDL_PollEvent( &event );

        switch (event.type) {

            case SDL_KEYDOWN: return;

            default: break;
        }
    }
}*/

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

/*
SDL_Surface* display_image(SDL_Window *win, SDL_Surface *img) {
  // Set the window to the same size as the image
  SDL_SetWindowSize(win, img->w, img->h);
  SDL_Surface *screen = SDL_GetWindowSurface(win);

  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

   Blit onto the screen surface
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateWindowSurface(win);

  // wait for a key
  wait_for_keypressed();

  // return the screen for further uses
  return screen;
}*/
