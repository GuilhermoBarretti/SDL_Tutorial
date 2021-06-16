#include "SDL.h"
#include "scene.hpp"
#include "game.hpp"

Scene::Scene(Game *_game)
{
	game = _game;
}

Scene::~Scene()
{

}

void Scene::HandleInput()
{
	SDL_Event event;

	// SDL_GetMouseState(&mouse_x, &mouse_y);

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_WINDOWEVENT:
				if (SDL_WINDOWEVENT_SIZE_CHANGED)
				{
					SDL_GetWindowSize(game->window, &(game->screen_width), &(game->screen_height));
					SDL_Log("w:%d h: %d\n", game->screen_width, game->screen_height);
				}
				break;
			case SDL_QUIT:
				SDL_Log("Quit");
				game->quit = true;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_DOWN:
						break;
					case SDLK_UP:
						break;
					case SDLK_LEFT:
						btn_left.Press();
						break;
					case SDLK_RIGHT:
						btn_right.Press();
						break;
					case SDLK_KP_PLUS:
						break;
					case SDLK_KP_MINUS:
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_DOWN:
						break;
					case SDLK_UP:
						break;
					case SDLK_LEFT:
						btn_left.Unpress();
						break;
					case SDLK_RIGHT:
						btn_right.Unpress();
						break;
					default:
						break;
				}
				break;
			default:
				break;
	    }
    }
}

void Scene::Update()
{
	if (btn_left.GetValue())
	{
		player.x -= player.velocity;
	}
	if (btn_right.GetValue())
	{
		player.x += player.velocity;
	}
}

void Scene::Draw()
{
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);

	SDL_Rect player_rect;
	player_rect.w = (int)(player.w * game->screen_width);
	player_rect.h = (int)(player.h * game->screen_height);

	player_rect.x = (int)(((player.x - (player.w/2))) * game->screen_width);
	player_rect.y = (int)(((player.y - (player.h/2))) * game->screen_height);
	SDL_RenderFillRect(game->renderer, &player_rect);

    SDL_RenderPresent(game->renderer);
}