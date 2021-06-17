#include "player.hpp"

Player::Player()
{
	// Coordenadas virtuais do jogo são 1x1;
	w = 0.20f;
	h = 0.05f;
	x = 0.5f; // centro da tela
	y = 0.90f;	// centro da tela
	velocity = 0.0005f;
}

Player::~Player()
{

}
