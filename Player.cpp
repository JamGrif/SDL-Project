#include "Player.h"

Player::Player(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency)
	:Entity(renderer, fileName, xpos, ypos, useTransparency)
{
	std::cout << "Player made" << std::endl;
}

Player::~Player()
{

}

void Player::MoveLeft()
{
	m_X-=m_Speed;
}

void Player::MoveRight()
{
	m_X+=m_Speed;
}

void Player::MoveJump()
{
	//to do

}
