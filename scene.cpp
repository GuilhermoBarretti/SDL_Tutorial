#include "SDL.h"
#include "scene.hpp"
#include "game.hpp"

Scene::Scene(Game *_game)
{
	game = _game;
	
	player.w = 100;
	player.h = 30;
	player.x = game->screen_width/2;
	player.y = game->screen_height - game->screen_height/6;
	player.velocity = 0.3f;
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
	// player.x = mouse_x - player.w/2;
	// player.y = mouse_y - player.h/2;

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
	player_rect.w = (int) player.w;
	player_rect.h = (int) player.h;
	player_rect.x = (int) player.x;
	player_rect.y = (int) player.y;
	SDL_RenderFillRect(game->renderer, &player_rect);

    SDL_RenderPresent(game->renderer);
}