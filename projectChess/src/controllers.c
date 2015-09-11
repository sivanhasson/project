#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include "controllers.h"

/*constructing controllers*/

controller_t* create_base_controller(int x, int y, int w, int h, controller_type type){

	controller_t * baseController = malloc(sizeof(controller_t));
	if (baseController == NULL){
		perror("ERROR: failed allocating baseController");
		return NULL;
	}
	return baseController;
}

controller_t * create_window(int w, int h, int red, int green, int blue){
	controller_t* window = create_base_controller(0,0, w,h,WINDOW);
	if(window == NULL){
		printf("ERROR: failed to create the window");
		return NULL;
	}
	SDL_WM_SetCaption("GAME","GAME");
	window->surface = SDL_SetVideoMode(w,h,0, SDL_HWSURFACE);
	if(window->surface == NULL){
		printf("ERROR: failed to set video mode: %s\n", SDL_GetError());
		return NULL;
	}
	if (SDL_FillRect(window->surface, 0, SDL_MapRGB(window->surface->format, red, green, blue)) < 0) {
		printf("ERROR: failed to fill window rect with color: %s\n", SDL_GetError());
		return NULL;
	}
	return window;
}

controller_t * create_panel(int x, int y, int w, int h, int red, int green, int blue){
	controller_t *panel = create_base_controller(x, y, w, h, PANEL);
	if(panel == NULL){
		printf("ERROR: failed creating the panel");
		return NULL;
	}
	panel->surface = SDL_CreateRGBSurface(0, w, h, 8, 0,0,0,0);
	if(panel->surface == NULL){
		printf("ERROR: failed creating RGB surface: %s\n", SDL_GetError());
		return NULL;
	}
	if (SDL_FillRect(panel->surface, NULL, SDL_MapRGB(panel->surface->format, red, green, blue)) < 0) {
		printf("ERROR: failed to fill panel rect with color: %s\n", SDL_GetError());
		return NULL;
	}
	return panel;
}

controller_t * create_image(char* imageFile, ){
	controller_t *image = create_base_controller(x, y, w, h, IMAGE);
	SDL_Surface *loadedImage = SDL_LoadBMP(imageFile);
	if (loadedImage == NULL) {
		printf("ERROR: failed to load image: %s\n", SDL_GetError());
		return NULL;
	}
	if (SDL_BlitSurface(img, image->srcRect, image->surface, image->dstRect) > 0) {
		SDL_FreeSurface(img);
		printf("ERROR: failed to blit image: %s\n", SDL_GetError());
		break;
	}

}

controller_t * create_button()



int main(void) {

	/* Initialize SDL and make sure it quits*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	controller_t *w = create_window();

	/* We finished drawing*/
	if (SDL_Flip(w->surface) != 0) {
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
	}

	/* Wait a little before closing*/
	SDL_Delay(2000);

	return 0;
}




/*
struct ui_tree{}


#define struct ui_tree ui_tree_t


ui_tree_t * UiTreeBuilder(possible_windows){
	switch(possible_windows)

	return ui_tree_t of the specific possible_windows
}


struct ui_tree_node{}


#define struct ui_tree_node ui_tree_node_t

*/