#include "SDL.h"
#include "scene.hpp"
#include "game.hpp"

Scene::Scene(Game *_game)
{
	game = _game;
	CreateBlocks();
}

Scene::~Scene()
{

}

void Scene::HandleInput()
{
	SDL_Event event;

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

	SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
	SDL_Rect block_rect;
	for (int i = 0; i < block_vector.size(); ++i)
	{
		block_rect.w = (int)(block_vector[i].w * game->screen_width);
		block_rect.h = (int)(block_vector[i].h * game->screen_height);
		block_rect.x = (int)(((block_vector[i].x - (block_vector[i].w/2))) * game->screen_width);
		block_rect.y = (int)(((block_vector[i].y - (block_vector[i].h/2))) * game->screen_height);
		SDL_RenderFillRect(game->renderer, &block_rect);
	}

    SDL_RenderPresent(game->renderer);
}


void Scene::CreateBlocks()
{
	int max_col = 10;
	int max_row = 6;

	float block_width = 0.09f;
	float block_height = 0.02f;
	float vertical_spacing = 0.2f;
	float start_height = 0.2f;

	for (int i = 0; i < max_col; ++i)
	{
		for (int j = 0; j < max_row; ++j)
		{
			Block temp_block;
			temp_block.x =  ((float) i/ (float) max_col) + (block_width/2) + (0.005f);
			temp_block.y = (((float) j/ (float) max_row) * vertical_spacing) + start_height;
			temp_block.w = block_width;
			temp_block.h = block_height;
			
			block_vector.push_back(temp_block);
		}
	}
}