#include "Player.h"

Player::Player(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency,Level* pLevel , std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, useTransparency, pLevel ,DefaultPicture)
{
	//player is 64 pixels wide and 128 pixels tall
	IdleAnimation = DefaultPicture;
	RunningAnimation = "Assets/Player - Running.bmp";

	m_Speed = 5;

	m_Width = 64;
	m_Height = 128;

}


Player::~Player()
{

}




