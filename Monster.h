#pragma once
#include "Creature.h"
class Monster :
	public Creature
{
public:
	Monster(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, Level* pLevel, std::string DefaultPicture = "");

	void Chase(int P_X, int P_Y);

private:


};

