#ifndef GAME_H
#define GAME_H

#include "SDL.h"

class Game 
{
public:
	int screen_width = 800;
	int screen_height = 600;

	bool quit = false;
	SDL_Window *window; 
	SDL_Renderer *renderer; 
	SDL_Surface *screen_surface;

	Game(){}
	~Game(){}
};

#endif