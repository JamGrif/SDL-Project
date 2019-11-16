#include "Player.h"

Player::Player(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency,Level* pLevel , std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, useTransparency, pLevel ,DefaultPicture)
{
	//player is 64 pixels wide and 128 pixels tall
	IdleAnimation = DefaultPicture;
	RunningAnimation = "Assets/Player - Running.bmp";

	m_Speed = 10;
	m_JumpSpeed = 15;
	m_MaxJumpHeight = 10;

	m_Width = 64;
	m_Height = 64;

	//Players X and Y position is based on the P within the level text file. 
	//First find what vector position P is in
	
}


Player::~Player()
{

}

void Player::FindSpawnPoint()
{
	


}




