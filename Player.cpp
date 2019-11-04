#include "Player.h"

Player::Player(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, useTransparency, DefaultPicture)
{
	//player is 64 pixels wide and 128 pixels tall
	IdleAnimation = DefaultPicture;
	RunningAnimation = "Assets/Player - Running.bmp";

	m_Speed = 3;

}


Player::~Player()
{

}




