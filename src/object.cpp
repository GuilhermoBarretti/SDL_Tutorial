#include "object.hpp"
#include "SDL.h"

Object::Object()
{

}

Object::~Object()
{
	SDL_DestroyTexture(texture);
}