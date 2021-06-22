#include "player.hpp"

Player::Player()
{
	// Coordenadas virtuais do jogo são 1x1;
	size.x = 0.20f;
	size.y = 0.05f;
	
	position.x = 0.5f; // centro da tela
	position.y = 0.90f;	// centro da tela
	velocity.x = 0.0005f;
}

Player::~Player()
{

}
