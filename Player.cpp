#include "Player.h"

Player::Player(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency, std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, pLevel, useTransparency, DefaultPicture)
{
	//player is 64 pixels wide and 128 pixels tall
	IdleAnimation = DefaultPicture;

	m_Acceleration = 7;

	m_JumpSpeed = 7;
	m_CurrentJumpSpeed = m_JumpSpeed;
	m_MaxJumpTick = 7;

	m_Width = 53;
	m_Height = 51;

	//Players X and Y position is based on the P within the level text file. 
	//First find what vector position P is in
	
}


Player::~Player()
{

}



void Player::FindSpawnPoint()
{
	


}




