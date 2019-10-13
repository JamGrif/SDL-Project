#pragma once
#include "Creature.h"
class Monster :
	public Creature
{
public:
	Monster(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture = "");

private:


};

