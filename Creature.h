#pragma once
#include "Entity.h"
class Creature :
	public Entity
{
public:
	Creature(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string animation = "");


	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveJump();


protected:
	int m_Speed = 4;
	int Rcount = 0;
	int Lcount = 0;

	std::string IdleAnimation;
	std::string RunningAnimation;

};

