#include "SDL.h"
#include "scene.hpp"
#include "game.hpp"
#include <algorithm>
#include <glm/gtx/exterior_product.hpp>

# define PI 3.14159265358979323846

Scene::Scene(Game *_game)
{
	ball_velocity = 0.0001f;
	game = _game;
	
	CreateBlocks();

	ball.position.x = 0.5f;
	ball.position.y = 0.5f;
	ball.size.x = 0.025f;
	ball.size.y = 0.020f;
	ball.velocity.x = ball_velocity;
	ball.velocity.y = ball_velocity;

	ball.velocity.x = cosf((7 * PI)/4) * ball_velocity;
	ball.velocity.y = -sinf((7 * PI)/4) * ball_velocity;

	ball.texture = game->LoadTexture("resources/ball.png");
	if (ball.texture == NULL)
	{
		printf("error loading texture\n");
	}

	block_texture = game->LoadTexture("resources/block.png");
	if (block_texture == NULL)
	{
		printf("error loading texture\n");
	}

	player.texture = game->LoadTexture("resources/player.png");
	if (block_texture == NULL)
	{
		printf("error loading texture\n");
	}
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
					// SDL_Log("w:%d h: %d\n", game->screen_width, game->screen_height);
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
	ball.collided = false;

	if (btn_left.GetValue())
	{
		player.position.x -= player.velocity.x;
	}
	if (btn_right.GetValue())
	{
		player.position.x += player.velocity.x;
	}
	
	// Update Ball Position
	ball.position += ball.velocity;

	CheckBoundaries();
	CheckCollisionBallPlayer();
	CheckCollisionBallBlock();
}

void Scene::CheckCollisionBallBlock()
{
	for (Block &block: block_vector)
	{
		if (block.active)
		{
			BallBlockCollisionRectangle(block);
		}
	}
}

Direction Scene::VectorDirection(Block block)
{
	Direction direction;

	glm::vec2 block_top_right = glm::vec2(block.size.x/2, -block.size.y/2);
	glm::vec2 block_top_left = glm::vec2(-block.size.x/2, -block.size.y/2);
	glm::vec2 block_bottom_left = glm::vec2(-block.size.x/2, block.size.y/2);
	glm::vec2 block_bottom_right = glm::vec2(block.size.x/2, block.size.y/2);

	glm::vec2 distance = ball.position - block.position;

	if (glm::cross(block_bottom_right, distance) <= 0 &&
		glm::cross(distance, block_top_right) <= 0)
	{
		return RIGHT;
	}

	if (glm::cross(block_top_right, distance) <= 0 &&
		glm::cross(distance, block_top_left) <= 0)
	{
		return TOP;
	}

	if (glm::cross(block_top_left, distance) <= 0 &&
		glm::cross(distance, block_bottom_left) <= 0)
	{
		return LEFT;
	}

	if (glm::cross(block_bottom_left, distance) <= 0 &&
		glm::cross(distance, block_bottom_right) <= 0)
	{
		return BOTTOM;
	}

	return (Direction) -1;
}

void Scene::BallCollisionResolution(Direction direction, Block &block)
{
	ball.collided = true;
	block.active = false;

	switch (direction)
	{
		case TOP:
			ball.velocity.y = -ball.velocity.y;
			ball.position.y = block.position.y - (ball.size.y/2) - (block.size.y/2);
			break;
		case BOTTOM:
			ball.velocity.y = -ball.velocity.y;
			ball.position.y = block.position.y + (ball.size.y/2) + (block.size.y/2);
			break;
		case LEFT:
			ball.velocity.x = -ball.velocity.x;
			ball.position.x = block.position.x - (ball.size.x/2) - (block.size.x/2);
			break;
		case RIGHT:
			ball.velocity.x = -ball.velocity.x;
			ball.position.x = block.position.x + (ball.size.x/2) + (block.size.x/2);
			break;
		default:
			printf("none\n");
			break;
	}
}

// colisão retângulo - retângulo
void Scene::BallBlockCollisionRectangle(Block &block)
{
	if ((ball.position.x + (ball.size.x/2) > block.position.x - (block.size.x/2) &&
		 ball.position.x - (ball.size.x/2) < block.position.x + (block.size.x/2))&&
		(ball.position.y + (ball.size.y/2) > block.position.y - (block.size.y/2) &&
		 ball.position.y - (ball.size.y/2) < block.position.y + (block.size.y/2)))
	{
		Direction direction = VectorDirection(block);
		BallCollisionResolution(direction, block);
	}
}

// outro tipo de colisão
// circulo - retangulo
void Scene::BallBlockCollisionCircle(Block &block)
{
	float testX, testY;
	float distX, distY, distance;

	if (ball.position.x < block.position.x)
	{
		testX = block.position.x; // left edge
	}
	else if (ball.position.x > block.position.x + block.size.x)
	{
		testX = block.position.x + block.size.x; // right edge
	} 

	if (ball.position.y < block.position.y)
	{
		testY = block.position.y; // top edge
	}
	else if (ball.position.y > block.position.y + block.size.y)
	{
		testY = block.position.y + block.size.y; // bottom edge
	}
	// get distance from closest edges
	distX = block.position.x - testX;
	distY = block.position.y - testY;
	distance = sqrt((distX*distX) + (distY*distY));

	// if the distance is less than the radius, collision!
	if (distance <= block.size.x)
	{
		// Direction direction = VectorDirection(block);
		// BallCollisionResolution(direction, &block);
	}
}

void Scene::CheckCollisionBallPlayer()
{
	if (((ball.position.x + (ball.size.x/2) > player.position.x - (player.size.x/2)) &&
		 (ball.position.x + (ball.size.x/2) < player.position.x + (player.size.x/2))) ||
		((ball.position.x - (ball.size.x/2) > player.position.x + (player.size.x/2)) &&
		 (ball.position.x - (ball.size.x/2) < player.position.x - (player.size.x/2))))
	{
		if (((ball.position.y + (ball.size.y/2) > player.position.y - (player.size.y/2)) &&
		 	 (ball.position.y + (ball.size.y/2) < player.position.y + (player.size.y/2))) ||
		    ((ball.position.y - (ball.size.y/2) > player.position.y + (player.size.y/2)) &&
		     (ball.position.y - (ball.size.y/2) < player.position.y - (player.size.y/2))))
		{
			// A diferença para saber quão proximo ao centro do player a bola está
			// ball.position.x - player.position.x = distância entre os dois no eixo x
			// isso dividido por (player.size.x/2) faz com que esse valor esteja entre -1 e 1
			// sendo 0 o centro, -1 esquerda e 1 direita
			// depois somando 1 faz com que o valor seja entre 0 e 2
			// por fim divido por 2 para que o valor esteja entre 0 e 1
			float x_difference = (((ball.position.x - player.position.x)/(player.size.x/2)) + 1)/2;

			// fazemos clamp para o valor ficar entre 0.1 e 0.9
			// isso afetara quais serão os angulos minimos que ball será rebatido
			x_difference = std::clamp(x_difference, 0.1f, 0.9f);

			// posição y de ball é acima do player mais suas alturas
			ball.position.y = player.position.y - (player.size.y/2) - (ball.size.y/2);

			// com isso conseguimos calcular qual será o angulo com que ball será rebatido usando seno e cosseno
			ball.velocity.y = -sinf(x_difference * PI) * ball_velocity;
			ball.velocity.x = -cosf(x_difference * PI) * ball_velocity;
		}
	}
}

void Scene::CheckBoundaries()
{
	// Ball
	if (ball.position.x + (ball.size.x/2) > 1)
	{
		ball.position.x = 1 - ball.size.x/2;
		ball.velocity.x = -ball.velocity.x;
	}
	else if (ball.position.x - (ball.size.x/2) < 0)
	{
		ball.position.x = 0 + ball.size.x/2;
		ball.velocity.x = -ball.velocity.x;
	}

	if (ball.position.y + (ball.size.y/2) > 1)
	{
		ball.position.y = 1 - ball.size.y/2;
		ball.velocity.y = -ball.velocity.y;
	}
	else if (ball.position.y - (ball.size.y/2) < 0)
	{
		ball.position.y = 0 + ball.size.y/2;
		ball.velocity.y = -ball.velocity.y;
	}

	// Player
	if (player.position.x + (player.size.x/2) > 1) 
	{
		player.position.x = 1 - (player.size.x/2);
	}

	if (player.position.x - (player.size.x/2) < 0)
	{
		player.position.x = 0 + (player.size.x/2);
	}
}


void Scene::Draw()
{
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	DrawPlayer();
	DrawBlocks();
	DrawBall();

    SDL_RenderPresent(game->renderer);
}

void Scene::DrawPlayer()
{
	SDL_Rect player_rect;
	player_rect.w = (int)(player.size.x * game->screen_width);
	player_rect.h = (int)(player.size.y * game->screen_height);
	player_rect.x = (int)(((player.position.x - (player.size.x/2))) * game->screen_width);
	player_rect.y = (int)(((player.position.y - (player.size.y/2))) * game->screen_height);
	SDL_RenderCopy(game->renderer, player.texture, NULL, &player_rect);
}

void Scene::DrawBall()
{
	SDL_Rect ball_rect;
	ball_rect.w = (int)(ball.size.x * game->screen_width);
	ball_rect.h = (int)(ball.size.y * game->screen_height);
	ball_rect.x = (int)(((ball.position.x - (ball.size.x/2))) * game->screen_width);
	ball_rect.y = (int)(((ball.position.y - (ball.size.y/2))) * game->screen_height);

	SDL_RenderCopy(game->renderer, ball.texture, NULL, &ball_rect);
}

void Scene::DrawBlocks()
{
	// SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
	SDL_Rect block_rect;
	for (int i = 0; i < block_vector.size(); ++i)
	{
		if (block_vector[i].active)
		{
			block_rect.w = (int)(block_vector[i].size.x * game->screen_width);
			block_rect.h = (int)(block_vector[i].size.y * game->screen_height);
			block_rect.x = (int)(((block_vector[i].position.x - (block_vector[i].size.x/2))) * game->screen_width);
			block_rect.y = (int)(((block_vector[i].position.y - (block_vector[i].size.y/2))) * game->screen_height);
			SDL_RenderCopy(game->renderer, block_texture, NULL, &block_rect);
		}
	}
}

void Scene::CreateBlocks()
{
	int max_col = 10;
	int max_row = 6;

	float block_width = 0.1f;
	float block_height = 0.05f;
	float start_height = 0.1f;

	for (int i = 0; i < max_col; ++i)
	{
		for (int j = 0; j < max_row; ++j)
		{
			Block temp_block;
			temp_block.position.x = ((float) i/ (float) max_col) + (block_width/2);
			temp_block.position.y = (j * (block_height)) + start_height;
			temp_block.size.x = block_width;
			temp_block.size.y = block_height;
			temp_block.active = true;
			
			block_vector.push_back(temp_block);
		}
	}
}