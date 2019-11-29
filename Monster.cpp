#include "Monster.h"

Monster::Monster(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency, std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, pLevel, useTransparency, DefaultPicture)
{
	
	

	m_Acceleration = 1;
}

void Monster::Chase(int P_X, int P_Y)
{
	
}
