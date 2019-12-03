#include "Creature.h"

Creature::Creature(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency)
	:Entity(renderer, xpos, ypos, pLevel, useTransparency)

{

	//UpdateBitmap(CurrentPicture, true);

	levelinfo = pLevel;

}

//Moves the creature and checks for collision in the level vector
void Creature::Move()
{
	
	
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
	GetCollisionPosition(0, false);

	//Check if the player is grounded or not
	IsGrounded = levelinfo->IsWall(BotLeftPosX, BotLeftPosY+1, BotRightPosX, BotRightPosY+1) == true ? true : false;

	//std::cout << "IsGrounded equals " << IsGrounded << std::endl;
	//std::cout << "IsJumping equals " << IsJumping << std::endl;
	//std::cout << "AppliedGravity equals " << AppliedGravity << std::endl;
	//std::cout << "Velocity.y equals " << Velocity.y << std::endl;

	if (IsGrounded == false) //If the player is not grounded then apply gravity
	{
		if (!AppliedGravity) 
		{
			Velocity.y += m_Gravity;
			AppliedGravity = true;
		}
	}
	else 
	{
		AppliedGravity = false;
		Velocity.y = 0;
	}

	
	//If the character is jumping then apply jumping stuff
	if (IsJumping)
	{
		if (m_CurrentJumpTick < m_MaxJumpTick)
		{
			m_CurrentJumpSpeed--;
			Velocity.y -= m_CurrentJumpSpeed;
			m_CurrentJumpTick++;
		}
		else
		{
			AppliedGravity = false;
			IsJumping = false;
			m_CurrentJumpTick = 0;
			Velocity.y = 0;
			m_CurrentJumpSpeed = m_JumpSpeed;
		}

		//Check above the player and if they hit something then stop jumping
		if (levelinfo->IsWall(TopLeftPosX, TopLeftPosY-1, TopRightPosX, TopRightPosY-1) == true)
		{
			//std::cout << "Player hit something above them" << std::endl;
			AppliedGravity = false;
			IsJumping = false;
			m_CurrentJumpTick = 0;
			Velocity.y = 0;
			m_CurrentJumpSpeed = m_JumpSpeed;
		}
	}


	//Move the creature depending on velocity and if something is in the way
	TouchingRight = levelinfo->IsWall(TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY-2) == true ? true : false;
	if (Velocity.x > 0 && !TouchingRight) //Creature moving right 
	{
		Position.x += Velocity.x;
		CanMove = levelinfo->IsWall(TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY-2) == true ? false : true;
		if (!CanMove)
		{
			Velocity.x = 0;
		}
	}

	TouchingLeft = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY-2) == true ? true : false;
	if (Velocity.x < 0 && !TouchingLeft) //Creature moving left
	{
		Position.x += Velocity.x;
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY-2) == true ? false : true;
		if (!CanMove)
		{
			Velocity.x = 0;
		}
	}

	TouchingUp = levelinfo->IsWall(TopLeftPosX, TopLeftPosY-1, TopRightPosX, TopRightPosY-1) == true ? true : false;
	if (Velocity.y < 0 && !TouchingUp) //Creature moving up
	{
		Position.y += Velocity.y;
		CanMove = levelinfo->IsWall(TopLeftPosX, TopLeftPosY-1, TopRightPosX, TopRightPosY-1) == true ? false : true;
		if (!CanMove)
		{
			Velocity.y = 0;
		}
	}

	TouchingDown = levelinfo->IsWall(BotLeftPosX, BotLeftPosY+1, BotRightPosX, BotRightPosY+1) == true ? true : false;
	if (Velocity.y > 0 && !TouchingDown) //Creature moving down;
	{
		Position.y += Velocity.y;
		CanMove = levelinfo->IsWall(BotLeftPosX, BotLeftPosY+1, BotRightPosX, BotRightPosY+1) == true ? false : true;
		if (!CanMove)
		{
			Velocity.y = 0;
		}
	}

	if (Velocity.x > 0){}
	
	//Apply air resistance to velocity
	if (Velocity.x > 0) 
	{
		Velocity.x -= m_AirResistance;
	}
	else if (Velocity.x < 0)
	{
		Velocity.x += m_AirResistance;
	}	

}

void Creature::GetCollisionPosition(int SpeedModifyer, bool XPosChange)
{
	//SpeedModifyer is used for creatures that have a speed above 1. It allows them to get as close to an object as they can
	if (XPosChange) //X position is being changed
	{
		TopLeftPosX = Position.x + Velocity.x;
		TopLeftPosY = Position.y;

		TopRightPosX = (Position.x + (m_Width - 1)) + Velocity.x;
		TopRightPosY = Position.y;

		BotLeftPosX = Position.x + Velocity.x;
		BotLeftPosY = Position.y + (m_Height - 1);

		BotRightPosX = (Position.x + (m_Width - 1)) + Velocity.x;
		BotRightPosY = Position.y + (m_Height - 1);
	}
	else //Y position is being changed
	{
		TopLeftPosX = Position.x;
		TopLeftPosY = Position.y + Velocity.y;

		TopRightPosX = (Position.x + (m_Width - 1));
		TopRightPosY = Position.y + Velocity.y;

		BotLeftPosX = Position.x;
		BotLeftPosY = Position.y + (m_Height - 1) + Velocity.y;

		BotRightPosX = (Position.x + (m_Width - 1));
		BotRightPosY = Position.y + (m_Height - 1) + Velocity.y;
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




