#ifndef SCENE_H
#define SCENE_H

#include "button.hpp"

class Game;

class Scene
{
	Button btn_left, btn_right;
	SDL_Rect player;
	int velocity;
	int mouse_x, mouse_y;

	Game *game = NULL;
public:
	Scene(Game *_game);
	~Scene();

	void HandleInput();
	void Update();
	void Draw();
};

#endif