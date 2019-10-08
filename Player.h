#pragma once
#include "Entity.h"
class Player :
	public Entity
{
public:
	Player(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency);
	~Player();

	void MoveLeft();
	void MoveRight();
	void MoveJump();


private:
	int m_JumpPosition = 0;
	int m_Speed = 4;


};

