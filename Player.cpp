#include "Player.h"

Player::Player(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, useTransparency, DefaultPicture)
{
	IdleAnimation = DefaultPicture;
	RunningAnimation = "Assets/Player - Running.bmp";

	m_Speed = 3;
	Eaten = false;
}


Player::~Player()
{

}

void Player::PlayerEaten()
{
	Eaten = true;
}

bool Player::GetEaten()
{
	return Eaten;
}




