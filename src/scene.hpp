#ifndef SCENE_H
#define SCENE_H

#include <deque>
#include "button.hpp"
#include "player.hpp"
#include "block.hpp"

class Game;

class Scene
{
	Game *game = NULL;
	Button btn_left, btn_right;
	Player player;
	std::deque<Block> block_vector;

public:
	Scene(Game *_game);
	~Scene();

	void CreateBlocks();

	void HandleInput();
	void Update();
	void Draw();
};

#endif