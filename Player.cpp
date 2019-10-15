#include "Player.h"

Player::Player(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, useTransparency, DefaultPicture)
{
	IdleAnimation = DefaultPicture;
	RunningAnimation = "Assets/Player - Running.bmp";

	m_Speed = 5;

}


Player::~Player()
{

}

int Player::GetX()
{
	return m_X;
}

int Player::GetY()
{
	return m_Y;
}


