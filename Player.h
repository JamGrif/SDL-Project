#pragma once
#include "Creature.h"

class Player :
	public Creature
{
public:
	Player(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency,  std::string DefaultPicture = "");
	~Player();



	void FindSpawnPoint();

private:
	


};

