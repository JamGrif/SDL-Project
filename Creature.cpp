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
	if (!IsJumping) 
	{
		std::cout << "Player should start jumping!" << std::endl;
		IsJumping = true;
	}
	else 
	{
		std::cout << "Player is already jumping!" << std::endl;
	}

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

	//Collision stuff
	GetCollisionPosition(0, true);
	TempSpeed = m_Speed;

	if (Direction == 'u')
	{
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, TopRightPosX, TopRightPosY) == true ? false : true;
		if (!CanMove)
		{
			CloserToWall(m_Y, TopLeftPosX, TopLeftPosY, TopRightPosX, TopRightPosY, false, false);
		}
	}
	else if (Direction == 'd')
	{
		CanMove = levelinfo->IsWall(BotLeftPosX, BotLeftPosY, BotRightPosX, BotRightPosY) == true ? false : true;
		if (!CanMove)
		{
			CloserToWall(m_Y, BotLeftPosX, BotLeftPosY, BotRightPosX, BotRightPosY, true, false);
		}
	}
	else if (Direction == 'l')
	{
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY) == true ? false : true;
		if (!CanMove)
		{
			CloserToWall(m_X, TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY, false, true);
		}
	}
	else if (Direction == 'r')
	{
		CanMove = levelinfo->IsWall(TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY) == true ? false : true;
		if (!CanMove) 
		{
			CloserToWall(m_X, TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY, true, true);
		}
	}

	if (CanMove == false) 
	{
		m_X = m_PrevX;
		m_Y = m_PrevY;
	}
}

//Function allows a creature with a speed above 1 to get as close to the wall as they can
void Creature::CloserToWall(int &position, int &FirstX, int &FirstY, int &SecondX, int &SecondY, bool PositivePositionChange, bool XPosChange)
{
	while ((CanMove == false && TempSpeed != 0) || CanMove != true)
		{
			TempSpeed--;
			if (XPosChange) 
			{
				PositivePositionChange == true ? GetCollisionPosition(TempSpeed, true) : GetCollisionPosition(-TempSpeed, true);
			}
			else 
			{
				PositivePositionChange == true ? GetCollisionPosition(TempSpeed, false) : GetCollisionPosition(-TempSpeed, false);
			}
			
			if (levelinfo->IsWall(FirstX, FirstY, SecondX, SecondY) == false)
			{
				PositivePositionChange == true ? position += TempSpeed : position -= TempSpeed;
				CanMove = true;
			}
		}


}

void Creature::Physics()
{
	GetCollisionPosition(0, false);
	if (IsGrounded == true) //Check that the player is still grounded by looking below him
	{
		IsJumping = false;
		if (levelinfo->IsWall(BotLeftPosX, BotLeftPosY + 1, BotRightPosX, BotRightPosY + 1) == false) 
		{
			IsGrounded = false;
		}
	}

	if (IsGrounded == false) 
	{
		std::cout << "Player is falling" << std::endl;
		//first check if wall is below character. If so then isgrounded == true else move down
		if (levelinfo->IsWall(BotLeftPosX, BotLeftPosY+1, BotRightPosX, BotRightPosY+1) == true) 
		{
			IsGrounded = true;
		}
		else 
		{
			m_Y += m_Gravity;
		}
	}

	if (IsJumping) 
	{
		std::cout << "IsJumping If statement ran" << std::endl;

		if (m_CurrentJumpHeight <= m_MaxJumpHeight) 
		{
			Move('u');
			m_CurrentJumpHeight++;
		}
		




	}





}

void Creature::GetCollisionPosition(int SpeedModifyer, bool XPosChange)
{
	//SpeedModifyer is used for creatures that have a speed above 1. It allows them to get as close to an object as they can
	if (XPosChange) //X position is being changed
	{
		TopLeftPosX = m_X + SpeedModifyer;
		TopLeftPosY = m_Y;

		TopRightPosX = (m_X + (m_Width - 1)) + SpeedModifyer;
		TopRightPosY = m_Y;

		BotLeftPosX = m_X + SpeedModifyer;
		BotLeftPosY = m_Y + (m_Height - 1);

		BotRightPosX = (m_X + (m_Width - 1)) + SpeedModifyer;
		BotRightPosY = m_Y + (m_Height - 1);
	}
	else //Y position is being changed
	{
		TopLeftPosX = m_X;
		TopLeftPosY = m_Y + SpeedModifyer;

		TopRightPosX = (m_X + (m_Width - 1));
		TopRightPosY = m_Y + SpeedModifyer;

		BotLeftPosX = m_X;
		BotLeftPosY = m_Y + (m_Height - 1) + SpeedModifyer;

		BotRightPosX = (m_X + (m_Width - 1));
		BotRightPosY = m_Y + (m_Height - 1) + SpeedModifyer;



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
