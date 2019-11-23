#include "Creature.h"

Creature::Creature(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency, std::string DefaultPicture)
	:Entity(renderer, xpos, ypos, pLevel, useTransparency)

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
	if (!IsJumping && IsGrounded) //If player is currently not jumping and is grounded then set it so they are currently jumping
	{
		IsJumping = true;
		m_CurrentJumpHeight = 0;
	}
}

//Moves the creature and checks for collision in the level vector
void Creature::Move(char Direction)
{
	m_PrevX = m_X;
	m_PrevY = m_Y;

	if (Direction == 'u') 
	{
		//m_Y -= m_JumpSpeed;
		m_Y -= m_Speed;
	}
	else if (Direction == 'd') 
	{
		//m_Y += m_Gravity;
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
	/*GetCollisionPosition(0, true);
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
		TempSpeed = m_Gravity;
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

	//If they cant move into the next position then set their position back to where it was
	if (CanMove == false) 
	{
		m_X = m_PrevX;
		m_Y = m_PrevY;
	}
	*/
}

//Function allows a creature with a speed above 1 to get as close to the wall as they can. This avoids a gap between a creature and a wall if they meet the wall
void Creature::CloserToWall(float& position, float& FirstX, float& FirstY, float& SecondX, float& SecondY, bool PositivePositionChange, bool XPosChange)
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

//Funciton is ran every game loop to update players position based on stuff like jumping and gravity
void Creature::Physics()
{
	GetCollisionPosition(0, false);

	if (IsGrounded == false) //If the player is not grounded then check below them to see if they are
	{
		//If a wall is directly below then they are grounded
		if (levelinfo->IsWall(BotLeftPosX, BotLeftPosY + 1, BotRightPosX, BotRightPosY + 1) == true)
		{
			IsGrounded = true;
			//std::cout << "Player is grounded" << std::endl;
		}
		//Else apply gravity
		else
		{
			Move('d');
			//std::cout << "Player is falling" << std::endl;
		}
	}

	if (IsJumping) //If the character is jumping then apply jumping stuff
	{
		if (m_CurrentJumpHeight < m_MaxJumpHeight)
		{
			//std::cout << "Player just jumped" << std::endl;
			Move('u');
			m_CurrentJumpHeight++;
		}
		else 
		{
			IsJumping = false;
			m_CurrentJumpHeight = 0;
		}

		//Check above the player and if they hit something then stop jumping
		if (levelinfo->IsWall(TopLeftPosX, TopLeftPosY-1, TopRightPosX, TopRightPosY-1) == true)
		{
			//std::cout << "Player hit something above them" << std::endl;
			IsJumping = false;
		}
	}

	if (IsGrounded == true) //Check that the player is still grounded by looking below him
	{
		if (levelinfo->IsWall(BotLeftPosX, BotLeftPosY + 1, BotRightPosX, BotRightPosY + 1) == false)
		{
			IsGrounded = false;
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

int Creature::GetX()
{
	return m_X;
}

int Creature::GetY()
{
	return m_Y;
}

float Creature::GetSpeed()
{
	return m_Speed;
}
