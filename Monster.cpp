#include "Monster.h"

Monster::Monster(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency)
	:Creature(renderer, xpos, ypos, pLevel, useTransparency)
{
	
	

	m_Acceleration = 1;
}

void Monster::Chase(int P_X, int P_Y)
{
	
}
