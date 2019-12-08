#pragma once
#include "Creature.h"
#include "Player.h"
class Goomba :
	public Creature
{
public:
	Goomba(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, Player* pPlayer, bool useTransparency = true);

	void Update();


private:

	int PlayerX = 0;
	int PlayerY = 0;

	bool MovingRight = true;

	std::string GoombaSprite = "Assets/Goomba.bmp";

	Player* playerinfo;
};

