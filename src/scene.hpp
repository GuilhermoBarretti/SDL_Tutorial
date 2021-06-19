#ifndef SCENE_H
#define SCENE_H

#include <deque>
#include "button.hpp"
#include "player.hpp"
#include "block.hpp"
#include "ball.hpp"

class Game;

class Scene
{
	Game *game = NULL;
	Button btn_left, btn_right;
	Player player;
	float ball_velocity;
	Ball ball;
	std::deque<Block> block_vector;

public:
	Scene(Game *_game);
	~Scene();

	void CreateBlocks();
	void CheckBoundaries();
	void CheckCollisionBallPlayer();
	void CheckCollisionBallBlock();

	void BallBlockCollision(Block &block);
	void BallBlockCollision1(Block &block);
	void BallBlockCollision2(Block &block);

	void DrawPlayer();
	void DrawBall();
	void DrawBlocks();

	void HandleInput();
	void Update();
	void Draw();
};

#endif