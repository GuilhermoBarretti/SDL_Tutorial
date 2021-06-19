#include "SDL.h"
#include "scene.hpp"
#include "game.hpp"
#include <algorithm>

# define PI 3.14159265358979323846

Scene::Scene(Game *_game)
{
	ball_velocity = 0.00002f;
	game = _game;
	
	CreateBlocks();

	ball.x = 0.5f;
	ball.y = 0.5f;
	ball.w = 0.025f;
	ball.h = 0.020f;
	ball.velocity_x = ball_velocity;
	ball.velocity_y = ball_velocity;

	ball.velocity_x = cosf((7 * PI)/4) * ball_velocity;
	ball.velocity_y = -sinf((7 * PI)/4) * ball_velocity;
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
	if (btn_left.GetValue())
	{
		player.x -= player.velocity_x;
	}
	if (btn_right.GetValue())
	{
		player.x += player.velocity_x;
	}
	
	// Update Ball Position
	ball.x += ball.velocity_x;
	ball.y += ball.velocity_y;

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
			BallBlockCollision(block);
		}
	}
}

// colisão retângulo - retângulo
void Scene::BallBlockCollision(Block &block)
{
	// COLLIDIU NA VERTICAL
	if ((ball.x < block.x + (block.w/2) + (ball.w/2))  &&
		(ball.x > block.x - (block.w/2) - (ball.w/2)))
	{
		// EM BAIXO
		if (((ball.y + (ball.h/2) > block.y - (block.h/2))  &&
		 	 (ball.y + (ball.h/2) < block.y + (block.h/2))))
		{
			block.active = false;
			ball.velocity_y = -ball.velocity_y;
			ball.y = block.y - (ball.h/2) - (block.h/2);
			printf("Baixo\n");
		}
		// EM CIMA
		else
		if (((ball.y - (ball.h/2) < block.y + (block.h/2))  &&
		     (ball.y - (ball.h/2) > block.y - (block.h/2))))
		{
			block.active = false;
			ball.velocity_y = -ball.velocity_y;
			ball.y = block.y + (ball.h/2) + (block.h/2);
			printf("Cima\n");
		}
	}
	// essa parte nunca será executada
	else
	if ((ball.y < block.y + (block.h/2) + (ball.h/2))  &&
		(ball.y > block.y - (block.h/2) - (ball.h/2)))
	{
		if (((ball.x + (ball.w/2) > block.x - (block.w/2))  &&
		 	 (ball.x + (ball.w/2) < block.x + (block.w/2))))
		{
			printf("Direita\n");
			block.active = false;
			ball.velocity_x = -ball.velocity_x;
			ball.x = block.x - (ball.w/2) - (block.w/2);
		}
		else
		if (((ball.x - (ball.w/2) < block.x + (block.w/2))  &&
		     (ball.x - (ball.w/2) > block.x - (block.w/2))))
		{
			printf("Esquerda\n");
			block.active = false;
			ball.velocity_x = -ball.velocity_x;
			ball.x = block.x + (ball.w/2) + (block.w/2);
		}
	}
}

// testando outro tipo de colisão
// circulo - retangulo
// no momento não funcionando
void Scene::BallBlockCollision2(Block &block)
{
	// Vector from A to B
	float nx = ball.x - block.x;
	float ny = ball.y - block.y;

	// Closest point on A to center of B
	float closestx = nx;
	float closesty = ny;

	// Calculate half extents along each axis
	float x_extent = ((block.x + (block.w/2)) - (block.x - (block.w/2))) / 2;
		float y_extent = ((block.y + (block.h/2)) - (block.y - (block.h/2))) / 2;

	// Clamp point to edges of the AABB
	closestx = std::clamp(closestx, -x_extent, x_extent);
	closesty = std::clamp(closesty, -y_extent, y_extent);

	bool inside = false;
	if (nx == closestx && ny == closesty)
	{
		inside = true;

		// Find closest axis
		if(fabs( nx ) > fabs( ny ))
		{
			// Clamp to closest extent
			if(closestx > 0)
				closestx = x_extent;
			else
				closestx = -x_extent;
		}

		// y axis is shorter
		else
		{
		// Clamp to closest extent
			if(closesty > 0)
				closesty = y_extent;
			else
				closesty = -y_extent;
		}
	}

	float normalx = nx - closestx;
	float normaly = ny - closesty;
	float d = normalx * normaly;
	float r = ball.w/2;

		// Early out of the radius is shorter than distance to closest point and
		// Circle not inside the AABB
	if(d > r * r && !inside)
		// nao colidiu
		// return false;

		// Avoided sqrt until we needed
	d = sqrt(d);

		// Collision normal needs to be flipped to point outside if circle was
		// inside the AABB
	if(inside)
	{
		// m->normal = -n
		// m->penetration = r - d
	}
	else
	{
		// m->normal = n
		// m->penetration = r - d
	}

	// colidiu
	// return true;
}

// outro tipo de colisão
// circulo - retangulo
void Scene::BallBlockCollision1(Block &block)
{
	float testX, testY;
	float distX, distY, distance;

	if (ball.x < block.x)
	{
		testX = block.x; // left edge
	}
	else if (ball.x > block.x + block.w)
	{
		testX = block.x + block.w; // right edge
	} 

	if (ball.y < block.y)
	{
		testY = block.y; // top edge
	}
	else if (ball.y > block.y + block.h)
	{
		testY = block.y + block.h; // bottom edge
	}
	// get distance from closest edges
	distX = block.x - testX;
	distY = block.y - testY;
	distance = sqrt((distX*distX) + (distY*distY));

	// if the distance is less than the radius, collision!
	if (distance <= block.w)
	{
		//colidiu

	}
}

void Scene::CheckCollisionBallPlayer()
{
	if (((ball.x + (ball.w/2) > player.x - (player.w/2)) &&
		 (ball.x + (ball.w/2) < player.x + (player.w/2))) ||
		((ball.x - (ball.w/2) > player.x + (player.w/2)) &&
		 (ball.x - (ball.w/2) < player.x - (player.w/2))))
	{
		if (((ball.y + (ball.h/2) > player.y - (player.h/2)) &&
		 	 (ball.y + (ball.h/2) < player.y + (player.h/2))) ||
		    ((ball.y - (ball.h/2) > player.y + (player.h/2)) &&
		     (ball.y - (ball.h/2) < player.y - (player.h/2))))
		{
			// A diferença para saber quão proximo ao centro do player a bola está
			// ball.x - player.x = distância entre os dois no eixo x
			// isso dividido por (player.w/2) faz com que esse valor esteja entre -1 e 1
			// sendo 0 o centro, -1 esquerda e 1 direita
			// depois somando 1 faz com que o valor seja entre 0 e 2
			// por fim divido por 2 para que o valor esteja entre 0 e 1
			float x_difference = (((ball.x - player.x)/(player.w/2)) + 1)/2;

			// fazemos clamp para o valor ficar entre 0.1 e 0.9
			// isso afetara quais serão os angulos minimos que ball será rebatido
			x_difference = std::clamp(x_difference, 0.1f, 0.9f);

			// posição y de ball é acima do player mais suas alturas
			ball.y = player.y - (player.h/2) - (ball.h/2);

			// com isso conseguimos calcular qual será o angulo com que ball será rebatido usando seno e cosseno
			ball.velocity_y = -sinf(x_difference * PI) * ball_velocity;
			ball.velocity_x = -cosf(x_difference * PI) * ball_velocity;
		}
	}
}

void Scene::CheckBoundaries()
{
	// Ball
	if ((ball.x + (ball.w/2) > 1) || (ball.x - (ball.w/2) < 0))
	{
		ball.velocity_x = -ball.velocity_x;
	}

	if ((ball.y + (ball.h/2) > 1) || (ball.y - (ball.h/2) < 0))
	{
		ball.velocity_y = -ball.velocity_y;
	}

	// Player
	if (player.x + (player.w/2) > 1) 
	{
		player.x = 1 - (player.w/2);
	}

	if (player.x - (player.w/2) < 0)
	{
		player.x = 0 + (player.w/2);
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
	// Render Player
	SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
	SDL_Rect player_rect;
	player_rect.w = (int)(player.w * game->screen_width);
	player_rect.h = (int)(player.h * game->screen_height);
	player_rect.x = (int)(((player.x - (player.w/2))) * game->screen_width);
	player_rect.y = (int)(((player.y - (player.h/2))) * game->screen_height);
	SDL_RenderFillRect(game->renderer, &player_rect);
}

void Scene::DrawBall()
{
	// Render Ball
	SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
	SDL_Rect ball_rect;
	ball_rect.w = (int)(ball.w * game->screen_width);
	ball_rect.h = (int)(ball.h * game->screen_height);
	ball_rect.x = (int)(((ball.x - (ball.w/2))) * game->screen_width);
	ball_rect.y = (int)(((ball.y - (ball.h/2))) * game->screen_height);
	SDL_RenderFillRect(game->renderer, &ball_rect);
}

void Scene::DrawBlocks()
{
	// Render Blocks
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, 255);
	SDL_Rect block_rect;
	for (int i = 0; i < block_vector.size(); ++i)
	{
		if (block_vector[i].active)
		{
			block_rect.w = (int)(block_vector[i].w * game->screen_width);
			block_rect.h = (int)(block_vector[i].h * game->screen_height);
			block_rect.x = (int)(((block_vector[i].x - (block_vector[i].w/2))) * game->screen_width);
			block_rect.y = (int)(((block_vector[i].y - (block_vector[i].h/2))) * game->screen_height);
			SDL_RenderFillRect(game->renderer, &block_rect);
		}
	}
}

void Scene::CreateBlocks()
{
	int max_col = 10;
	int max_row = 6;

	float block_width = 0.09f;
	float block_height = 0.08f;
	float vertical_spacing = block_height * 10;
	float start_height = 0.1f;

	for (int i = 0; i < max_col; ++i)
	{
		for (int j = 0; j < max_row; ++j)
		{
			Block temp_block;
			temp_block.x =   ((float) i/ (float) max_col) + (block_width/2) + (0.005f);
			temp_block.y = ((((float) j/ (float) max_row) * vertical_spacing) + (block_height/2)) + start_height;
			temp_block.w = block_width;
			temp_block.h = block_height;
			temp_block.active = true;
			
			block_vector.push_back(temp_block);
		}
	}
}