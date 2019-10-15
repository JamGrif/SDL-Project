#pragma once
#include "Creature.h"
class Player :
	public Creature
{
public:
	Player(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture = "");
	~Player();

	int GetX();
	int GetY();


private:
	
	

};

