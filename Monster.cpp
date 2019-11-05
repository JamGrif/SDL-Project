#include "Monster.h"

Monster::Monster(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, Level* pLevel, std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, useTransparency, pLevel, DefaultPicture)
{
	
	RunningAnimation = "Assets/Monster - Running.bmp";

	m_Speed = 1;
}

void Monster::Chase(int P_X, int P_Y)
{
	if (m_X < P_X)
	{
		
		//MoveRight();
		
	}

	else if (m_X > P_X)
	{
		
		//MoveLeft();
	}

	if (m_Y < P_Y)
	{
		
		//MoveDown();
	}

	else if (m_Y > P_Y)
	{
		
		//MoveUp();
	}
}
