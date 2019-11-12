#pragma once
#include "Entity.h"
#include "Level.h"
class Creature :
	public Entity
{
public:
	Creature(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, Level* level, std::string animation = "");

	void MoveJump();

	void Move(char Direction);

	void CloserToWall(int &position, int &FirstX, int &FirstY, int &SecondX, int &SecondY, bool PositivePositionChange, bool XPosChange);



	void Physics();

	void GetCollisionPosition(int speed, bool XPosChange);
	void DisplayPosition();


protected:
	int m_Speed = 0;
	int m_MaxJumpHeight = 0;
	int m_CurrentJumpHeight = 0;
	int TempSpeed = 0;
	int Rcount = 0;
	int Lcount = 0;
	int Ucount = 0;
	int Dcount = 0;

	

	int TopLeftPosX;
	int TopLeftPosY;
	int TopRightPosX;
	int TopRightPosY;
	int BotLeftPosX;
	int BotLeftPosY;
	int BotRightPosX;
	int BotRightPosY;

	int AnimationCount = 0;

	std::string IdleAnimation;
	std::string RunningAnimation;

	int m_Width;
	int m_Height;

	const int m_Gravity = 1;

	bool CanMove = false;
	
	bool IsGrounded = false;
	bool IsJumping = false;

	Level* levelinfo;

};

