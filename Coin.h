#pragma once
#include "Entity.h"
#include "Player.h"
class Coin :
	public Entity
{
public:
	Coin(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency = true);

	void Update(int PlayerX, int PlayerY);

	int IsCoinCollected();

private:

	bool CoinCollected = false;
	bool AppliedCoinAddition = false;



};

