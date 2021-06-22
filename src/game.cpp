#include "game.hpp"

SDL_Texture* Game::LoadTexture(std::string file_name)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified file_name
	SDL_Surface* loadedSurface = IMG_Load(file_name.c_str());
	if( loadedSurface == NULL )
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", file_name.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if( newTexture == NULL )
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", file_name.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}