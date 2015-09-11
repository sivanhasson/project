#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "GameFlow.h"

enum possible_windows {main_menu, player_selection_window, load_menu, setting_window, board_setting,
		add_piece, remove_piece, move_piece, game_window};

enum possible_windows Current_window;

typedef enum {WINDOW, PANEL, IMAGE, BUTTON} controller_type;

struct controller{
	controller_type type;
	SDL_Surface * surface;
	SDL_Surface * parent;
	int x,y;				/*location*/
	int w,h;
	SDL_Surface *src;
	SDL_Rect srcRect;
	SDL_Surface *dst;
	SDL_Rect dstRect;	/*location relative to parent panel or window*/
	int selected;
};

typedef struct controller controller_t;

/*FUNCTIONS*/

controller_t * create_base_controller(int x, int y, int w, int h, controller_type type);
controller_t * create_window(int w, int h, int red, int green, int blue);
controller_t * create_panel(int x, int y, int w, int h, int red, int green, int blue);
controller_t * create_image();
controller_t * create_button();

#endif /* CONTROLLER_H_ */
