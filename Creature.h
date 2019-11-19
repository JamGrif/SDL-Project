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

	void CloserToWall(float& position, float& FirstX, float& FirstY, float& SecondX, float& SecondY, bool PositivePositionChange, bool XPosChange);

	void Physics();

	void GetCollisionPosition(int speed, bool XPosChange);
	void DisplayPosition();

	int GetX();
	int GetY();


protected:
	float m_Speed = 0;
	int m_MaxJumpHeight = 0;
	int m_CurrentJumpHeight = 0;
	int m_JumpSpeed = 0;
	float TempSpeed = 0;

	int VectorPosition = 0;

	int Rcount = 0;
	int Lcount = 0;
	int Ucount = 0;
	int Dcount = 0;

	bool JustJumped = false;

	float TopLeftPosX;
	float TopLeftPosY;
	float TopRightPosX;
	float TopRightPosY;
	float BotLeftPosX;
	float BotLeftPosY;
	float BotRightPosX;
	float BotRightPosY;

	int AnimationCount = 0;

	std::string IdleAnimation;
	std::string RunningAnimation;

	int m_Width;
	int m_Height;

	const int m_Gravity = 5;

	bool CanMove = false;
	
	bool IsGrounded = false;
	bool IsJumping = false;

	Level* levelinfo;

};

