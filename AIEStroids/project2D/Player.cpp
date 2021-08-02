#include "Player.h"
#include "Renderer2D.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Update()
{

}

int Player::GetLives()
{
	return lives;
}

void Player::SetLives(int lives)
{
	this->lives = lives;
}
