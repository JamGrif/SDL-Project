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
	//std::cout << "Move function called" << std::endl;
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
		//std::cout << "Should be moving left" << std::endl;
		m_X -= m_Speed;
	}
	else if (Direction == 'r')
	{
		//std::cout << "Should be moving right" << std::endl;
		m_X += m_Speed;
	}

	//Collision stuff
	GetCollisionPosition(0);
	TempSpeed = m_Speed;

	if (Direction == 'u')
	{
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, TopRightPosX, TopRightPosY) == true ? false : true;
		/*while ((CanMove == false && TempSpeed != 0) || CanMove != true)
		{
			TempSpeed--;
			GetCollisionPosition(-TempSpeed);
			if (levelinfo->IsWall(TopLeftPosX, TopLeftPosY, TopRightPosX, TopRightPosY) == false)
			{
				m_Y -= TempSpeed;
				CanMove = true;
			}
		}*/
		
	}
	else if (Direction == 'd')
	{
		CanMove = levelinfo->IsWall(BotLeftPosX, BotLeftPosY, BotRightPosX, BotRightPosY) == true ? false : true;
		/*while ((CanMove == false && TempSpeed != 0) || CanMove != true)
		{
			TempSpeed--;
			GetCollisionPosition(TempSpeed);
			if (levelinfo->IsWall(BotLeftPosX, BotLeftPosY, BotRightPosX, BotRightPosY) == false)
			{
				m_Y += TempSpeed;
				CanMove = true;
			}
		}*/
	}
	else if (Direction == 'l')
	{
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY) == true ? false : true;
		while ((CanMove == false && TempSpeed != 0) || CanMove != true)
		{
			TempSpeed--;
			GetCollisionPosition(-TempSpeed);
			if (levelinfo->IsWall(TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY) == false)
			{
				m_X -= TempSpeed;
				CanMove = true;
			}
		}
	}
	else if (Direction == 'r')
	{
		CanMove = levelinfo->IsWall(TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY) == true ? false : true;
		while ((CanMove == false && TempSpeed != 0) || CanMove != true)
		{
			TempSpeed--;
			GetCollisionPosition(TempSpeed);
			if (levelinfo->IsWall(TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY) == false)
			{
				m_X += TempSpeed;
				CanMove = true;
			}
		}
	}

	if (CanMove == false) 
	{
		m_X = m_PrevX;
		m_Y = m_PrevY;
	}
}

void Creature::Physics()
{
	GetCollisionPosition(0);
	if (IsGrounded == false) 
	{
		std::cout << "Falling" << std::endl;
		//first check if wall is below character. If so then isgrounded == true else move down
		if (levelinfo->IsWall(BotLeftPosX, BotLeftPosY, BotRightPosX, BotRightPosY) == true) 
		{
			IsGrounded = true;
		}
		else 
		{
			m_Y += m_Gravity;
		}
	}







}

void Creature::GetCollisionPosition(int SpeedModifyer)
{
	//SpeedModifyer is used for creatures that have a speed above 1. It allows them to get as close to an object as they can
	TopLeftPosX = m_X + SpeedModifyer;
	TopLeftPosY = m_Y;

	TopRightPosX = (m_X + (m_Width - 1)) + SpeedModifyer;
	TopRightPosY = m_Y;

	BotLeftPosX = m_X + SpeedModifyer;
	BotLeftPosY = m_Y + (m_Height - 1);

	BotRightPosX = (m_X + (m_Width - 1)) + SpeedModifyer;
	BotRightPosY = m_Y + (m_Height - 1);
}

void Creature::DisplayPosition()
{
	std::cout << "Creatures position is:" << std::endl;
	std::cout << "Top left pos is " << TopLeftPosX << "," << TopLeftPosY << std::endl;
	std::cout << "Top right pos is " << TopRightPosX << "," << TopRightPosY << std::endl;
	std::cout << "Bottom left pos is " << BotLeftPosX << "," << BotLeftPosY << std::endl;
	std::cout << "Bottom right pos is " << BotRightPosX << "," << BotRightPosY << std::endl;
}
