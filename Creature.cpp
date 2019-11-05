#include "Creature.h"

Creature::Creature(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, Level* pLevel, std::string DefaultPicture)
	:Entity(renderer, xpos, ypos, useTransparency)

{
	IdleAnimation = DefaultPicture;

	if (IdleAnimation == "") 
	{
		IdleAnimation = "Assets/MissingTexture.bmp";
	}
	UpdateBitmap(IdleAnimation, true);

	levelinfo = pLevel;

}


void Creature::MoveJump()
{
	

}

void Creature::Move(char Direction)
{
	m_PrevX = m_X;
	m_PrevY = m_Y;

	if (Direction == 'u') 
	{
		m_Y -= m_Speed;
	}
	else if (Direction == 'd') 
	{
		m_Y += m_Speed;
	}
	else if (Direction == 'l')
	{
		m_X -= m_Speed;
	}
	else if (Direction == 'r')
	{
		m_X += m_Speed;
	}

	TopLeftPosX = m_X;
	TopLeftPosY = m_Y;

	TopRightPosX = m_X + m_Width - 1;
	TopRightPosY = m_Y;

	BotLeftPosX = m_X;
	BotLeftPosY = m_Y + m_Height - 1;

	BotRightPosX = m_X + m_Width - 1;
	BotRightPosY = m_Y + m_Height - 1;

	if (Direction == 'u')
	{
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, TopRightPosX, TopRightPosY) == true ? false : true;
	}
	else if (Direction == 'd')
	{
		CanMove = levelinfo->IsWall(BotLeftPosX, BotRightPosY, BotRightPosX, BotRightPosY) == true ? false : true;
	}
	else if (Direction == 'l')
	{
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY) == true ? false : true;
	}
	else if (Direction == 'r')
	{
		CanMove = levelinfo->IsWall(TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY) == true ? false : true;
	}

	if (CanMove == false) 
	{
		m_X = m_PrevX;
		m_Y = m_PrevY;
	}

	
}

void Creature::DisplayPosition() 
{
	
	std::cout << "Creatures position is:" << std::endl;
	std::cout << "Top left pos is " << TopLeftPosX << "," << TopLeftPosY << std::endl;
	std::cout << "Top right pos is " << TopRightPosX << "," << TopRightPosY << std::endl;
	std::cout << "Bottom left pos is " << BotLeftPosX << "," << BotLeftPosY << std::endl;
	std::cout << "Bottom right pos is " << BotRightPosX << "," << BotRightPosY << std::endl;



}
