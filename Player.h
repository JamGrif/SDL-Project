#pragma once
#include "Creature.h"

class Player :
	public Creature
{
public:
	Player(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency);
	~Player();

	void Move(char direction);

	void Physics();

	void SpriteUpdate(); 

	void FindSpawnPoint();

private:
	std::string SavedCurrentPicture = "";

	//Standing still sprites
	std::string PlayerR = "Assets/PlayerR.bmp";
	std::string PlayerL = "Assets/PlayerL.bmp";

	//Running sprites
	int m_CurrentFrame = 0;
	std::string PlayerRunL[3];
	std::string PlayerRunR[3];

	//Jumping sprite
	std::string PlayerJumpR = "Assets/PlayerJumpR.bmp";
	std::string PlayerJumpL = "Assets/PlayerJumpL.bmp";


};

