#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Game 
{
public:
	int screen_width = 800;
	int screen_height = 800;

	bool quit = false;
	SDL_Window *window = NULL; 
	SDL_Renderer *renderer = NULL; 

	Game(){}
	~Game(){}

	SDL_Texture* LoadTexture(std::string file_name);
};

#endif