#ifndef OBJECT_H
#define OBJECT_H

#include "glm.hpp"

class SDL_Texture;

class Object
{
public:
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 velocity;

	SDL_Texture *texture = NULL;

	Object();
	~Object();
};

#endif