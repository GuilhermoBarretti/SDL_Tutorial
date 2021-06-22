#include "game.hpp"

SDL_Texture* Game::LoadTexture(std::string file_name)
{
	SDL_Texture* return_texture = NULL;
	SDL_Surface* loaded_surface = IMG_Load(file_name.c_str());
	if( loaded_surface == NULL )
	{
		printf("Erro ao carregar imagem %s! SDL_image Error: %s\n", file_name.c_str(), IMG_GetError());
		SDL_FreeSurface(loaded_surface);
		return NULL;
	}

	return_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
	if( return_texture == NULL )
	{
		printf("Erro ao criar texture de %s! SDL Error: %s\n", file_name.c_str(), SDL_GetError());
		SDL_FreeSurface(loaded_surface);
		return NULL;
	}

	SDL_FreeSurface(loaded_surface);

	return return_texture;
}