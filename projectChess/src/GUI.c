#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>

enum possible_windows {main_menu, player_selection_window, load_menu, setting_window, board_setting,
		add_piece, remove_piece, move_piece, game_window};

enum possible_windows Current_window;

struct controler{
	SDL_Surface * surface;
};

typedef struct controler controler_t;

controler_t * create_window(){
	controler_t *w = NULL;
	SDL_WM_SetCaption("Sivan","Hasson");
	w->surface = SDL_SetVideoMode(640,480,0,0);
	return w;
}

//controler_t * create_panel()

//controler_t * create_label()

//controler_t * create_image()

//controler_t * create_button()


//enum control_type {...};

int main(void) {

	/* Initialize SDL and make sure it quits*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("ERROR: unable to init SDL: %s\n", SDL_GetError());
		return 1;
	}
	atexit(SDL_Quit);

	controler_t *w = create_window();

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