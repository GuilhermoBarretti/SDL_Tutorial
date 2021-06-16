#include "player.hpp"

Player::Player()
{
	// Coordenadas virtuais do jogo são 1x1;
	w = 0.20f;
	h = 0.1f;
	x = 0.5f; // centro da tela
	y = 0.85f;	// centro da tela
	velocity = 0.0005f;
}

Player::~Player()
{

}
