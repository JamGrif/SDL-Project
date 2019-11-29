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
	

	if (Direction == 'u') 
	{
		//m_Y -= m_JumpSpeed;
		Velocity.y -= m_Acceleration;
	}
	else if (Direction == 'd') 
	{
		//m_Y += m_Gravity;
		Velocity.y += m_Acceleration;
	}
	else if (Direction == 'l')
	{
		Velocity.x -= m_Acceleration;
	}
	else if (Direction == 'r')
	{
		Velocity.x += m_Acceleration;
	}
	
}

//Function allows a creature with a speed above 1 to get as close to the wall as they can. This avoids a gap between a creature and a wall if they meet the wall
void Creature::CloserToWall(float& position, float& FirstX, float& FirstY, float& SecondX, float& SecondY, bool PositivePositionChange, bool XPosChange, float& VelocityDirection)
{
	while ((CanMove == false && VelocityDirection != 0) || CanMove != true)
	{
		//std::cout << "test" << std::endl;
		//if (VelocityDirection > 0){ VelocityDirection--; }
		//else { VelocityDirection++; }
		VelocityDirection--;
		if (XPosChange) 
		{				
			//std::cout << "XPosChange is true" << std::endl;
			//std::cout << "XPosChange is " << PositivePositionChange << std::endl;
			PositivePositionChange == true ? GetCollisionPosition(VelocityDirection, true) : GetCollisionPosition(-VelocityDirection, true);
			//VelocityDirection = 0;
		}
		else 
		{
			//std::cout << "XPosChange is false" << std::endl;
			PositivePositionChange == true ? GetCollisionPosition(VelocityDirection, false) : GetCollisionPosition(-VelocityDirection, false);
		}
		
		
		if (levelinfo->IsWall(FirstX, FirstY, SecondX, SecondY) == false) //here error
		{
			PositivePositionChange == true ? position += VelocityDirection : position -= VelocityDirection;
			CanMove = true;
		}
	}


}

//Funciton is ran every game loop to update players position based on stuff like jumping and gravity
void Creature::Physics()
{
	//Save creatures previous position so they can move back if they cant move
	m_PrevX = Position.x;
	m_PrevY = Position.y;

	//If Velocity exceeds MaxVelocity then lower Velocity down to MaxVelocity  
	if (Velocity.x > m_MaxVelocity) { Velocity.x = m_MaxVelocity; }
	if (Velocity.x < -m_MaxVelocity) { Velocity.x = -m_MaxVelocity; }

	if (Velocity.y > m_MaxVelocity) { Velocity.y = m_MaxVelocity; }
	if (Velocity.y < -m_MaxVelocity) { Velocity.y = -m_MaxVelocity; }

	//Get the collision position of creature
	GetCollisionPosition(0, true);

	//Check if player is grounded
	if (IsGrounded == false) //If the player is not grounded then check below them to see if they are
	{
		//If a wall is directly below then they are grounded
		if (levelinfo->IsWall(BotLeftPosX, BotLeftPosY + 1, BotRightPosX, BotRightPosY + 1) == true)
		{
			IsGrounded = true;
			
		}
		//Else apply gravity
		else
		{
			//std::cout << "gravity" << std::endl;
			/*if (Velocity.y -= m_Gravity == Velocity.y < 0) 
			{
				Velocity.y = 0;
			}
			else 
			{
				Velocity.y += m_Gravity;
			}*/
			//Velocity.y += m_Gravity;
			
		}
	}

	//Move the creature depending on velocity
	Position.x += Velocity.x;
	Position.y += Velocity.y;

	
	if (Velocity.x > 0) //Creature moving right 
	{
		std::cout << "moving right" << std::endl;
		CanMove = levelinfo->IsWall(TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY) == true ? false : true;
		if (!CanMove)
		{
			CloserToWall(Position.x, TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY, true, true, Velocity.x);
			Velocity.x = 0;
		}
	}
	else if (Velocity.x < 0) //Creature moving left
	{
		std::cout << "moving left" << std::endl;
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY) == true ? false : true;
		if (!CanMove)
		{
			CloserToWall(Position.x, TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY, false, true, Velocity.x);
			Velocity.x = 0;
		}
	}
	else 
	{
		std::cout << "not changing x direction" << std::endl;
	}

	GetCollisionPosition(0, false);
	if (Velocity.y > 0) //Creature moving up
	{
		std::cout << "Moving up" << std::endl;
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY-1, TopRightPosX, TopRightPosY-1) == true ? false : true;
		if (!CanMove)
		{
			CloserToWall(Position.y, TopLeftPosX, TopLeftPosY, TopRightPosX, TopRightPosY, false, false, Velocity.y);
			Velocity.y = 0;
		}
	}
	else if (Velocity.y < 0) //Creature moving down;
	{
		std::cout << "Moving down" << std::endl;
		CanMove = levelinfo->IsWall(BotLeftPosX, BotLeftPosY+1, BotRightPosX, BotRightPosY+1) == true ? false : true;
		if (!CanMove)
		{
			CloserToWall(Position.y, BotLeftPosX, BotLeftPosY, BotRightPosX, BotRightPosY, true, false, Velocity.y);
			Velocity.y = 0;
		}
	}
	else 
	{
		std::cout << "not changing y direction" << std::endl;
	}

	//Apply air resistance to velocity
	if (Velocity.x > 0) 
	{
		Velocity.x -= m_AirResistance;
	}
	else if (Velocity.x < 0)
	{
		Velocity.x += m_AirResistance;
	}

	if (Velocity.y > 0)
	{
		Velocity.y -= m_AirResistance;
	}
	else if (Velocity.y < 0)
	{
		Velocity.y += m_AirResistance;
	}




	if (CanMove == false)
	{
		std::cout << ("cant move") << std::endl;
		Position.x = m_PrevX;
		Position.y = m_PrevY;
	}
	

	
	/* 
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
	}*/

	

	





}

void Creature::GetCollisionPosition(int SpeedModifyer, bool XPosChange)
{
	//SpeedModifyer is used for creatures that have a speed above 1. It allows them to get as close to an object as they can
	if (XPosChange) //X position is being changed
	{
		TopLeftPosX = Position.x + SpeedModifyer;
		TopLeftPosY = Position.y;

		TopRightPosX = (Position.x + (m_Width - 1)) + SpeedModifyer;
		TopRightPosY = Position.y;

		BotLeftPosX = Position.x + SpeedModifyer;
		BotLeftPosY = Position.y + (m_Height - 1);

		BotRightPosX = (Position.x + (m_Width - 1)) + SpeedModifyer;
		BotRightPosY = Position.y + (m_Height - 1);
	}
	else //Y position is being changed
	{
		TopLeftPosX = Position.x;
		TopLeftPosY = Position.y + SpeedModifyer;

		TopRightPosX = (Position.x + (m_Width - 1));
		TopRightPosY = Position.y + SpeedModifyer;

		BotLeftPosX = Position.x;
		BotLeftPosY = Position.y + (m_Height - 1) + SpeedModifyer;

		BotRightPosX = (Position.x + (m_Width - 1));
		BotRightPosY = Position.y + (m_Height - 1) + SpeedModifyer;
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




