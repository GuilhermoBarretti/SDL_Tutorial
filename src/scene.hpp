#ifndef SCENE_H
#define SCENE_H

#include "button.hpp"
#include "player.hpp"

class Game;

class Scene
{
	Button btn_left, btn_right;
	Player player;

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