#define SDL_MAIN_HANDLED 
#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"
#include "game.hpp"
#include "scene.hpp"

//cl main.cpp scene.cpp button.cpp player.cpp /Iinclude SDL2main.lib SDL2.lib SDL2_image.lib

/*
	Breakout Game
	- 
	- Usar surfaces
*/

int main(int argc, char* argv[])
{
	Game *game = new Game();
	Scene *scene = new Scene(game);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
		fprintf(stderr, "could not initialize sdl2_image: %s\n", IMG_GetError());
		return false;
	}

    game->window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        game->screen_width,                // width, in pixels
        game->screen_height,               // height, in pixels
        SDL_WINDOW_RESIZABLE			   // flags - see below
    );
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);

    while(!game->quit)
    {
    	scene->HandleInput();
    	scene->Update();
    	scene->Draw();
    }

    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    
    SDL_Quit();

    return 0;
}


// static SDL_Surface* LoadImage(std::string path)
// {
// 	SDL_Surface* img = IMG_Load(path.c_str());

// 	if (img == NULL)
// 	{
// 		fprintf(stderr, "could not load image: %s\n", IMG_GetError());
// 		return NULL;
// 	}

// 	SDL_Surface* optimizedImg = SDL_ConvertSurface(img, screen_surface->format, 0);

// 	if (optimizedImg == NULL) 
// 		fprintf(stderr, "could not optimize image: %s\n", SDL_GetError());
// 	SDL_FreeSurface(img);
	
// 	return optimizedImg;
// }