#include "SDL.h"   /* All SDL App's need this */
#include <stdio.h>


    void display_bmp(char *file_name, SDL_Surface *screen)
    {
        SDL_Surface *image;

        /* Load the BMP file into a surface */
        image = SDL_LoadBMP(file_name);
        if (image == NULL) {
            fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
            return;
        }

        /*
         * Palettized screen modes will have a default palette (a standard
         * 8*8*4 colour cube), but if the image is palettized as well we can
         * use that palette for a nicer colour matching
         */

        if (image->format->palette && screen->format->palette) {
        SDL_SetColors(screen, image->format->palette->colors, 0, image->format->palette->ncolors);
        }

        SDL_Delay(2000);

        /* Blit onto the screen surface */
        if(SDL_BlitSurface(image, NULL, screen, NULL) < 0)
            fprintf(stderr, "BlitSurface error: %s\n", SDL_GetError());

        SDL_UpdateRect(screen, 0, 0, image->w, image->h);


        SDL_Delay(2000);

        /* Free the allocated BMP surface */
        SDL_FreeSurface(image);
    }


int main(int argc, char *argv[]) {

    printf("Initializing SDL.\n");

    SDL_Surface *screen;

    /* Initialize the SDL library */
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    /* Clean up on exit */
    atexit(SDL_Quit);


    /* Have a preference for 8-bit, but accept any depth */
    screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE|SDL_ANYFORMAT);
    if ( screen == NULL ) {
        fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
                        SDL_GetError());
        exit(1);
    }
    printf("Set 640x480 at %d bits-per-pixel mode\n",
           screen->format->BitsPerPixel);

    display_bmp("test.bmp", screen);

}

