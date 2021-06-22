#define SDL_MAIN_HANDLED 
#include "stdio.h"
#include "game.hpp"
#include "scene.hpp"

int main(int argc, char* argv[])
{
    Game *game = new Game();
    Scene *scene = NULL;

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

    scene = new Scene(game);

    while(!game->quit)
    {
    	scene->HandleInput();
    	scene->Update();
    	scene->Draw();
    }

    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    
    IMG_Quit();
    SDL_Quit();

    return 0;
}