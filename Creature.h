#pragma once
#include "Entity.h"

class Creature :
	public Entity
{
public:
	Creature(SDL_Renderer* renderer, int xpos, int ypos, Level* plevel, bool useTransparency);

	virtual void Move();

	void CloserToWall(float& position, float& FirstX, float& FirstY, float& SecondX, float& SecondY, bool PositivePositionChange, bool XPosChange, float &VelocityDirection);

	virtual void Physics();

	void GetCollisionPosition(int speed, bool XPosChange);
	void DisplayPosition();

	
	


protected:
	//Movement
	float m_Acceleration = 0;

	const float m_MaxVelocity = 10;
	//const float m_Friction = 1;
	const float m_AirResistance = 1;
	const float m_Gravity = 3;

	float m_MaxJumpTick = 0;
	float m_CurrentJumpTick = 0;
	float m_CurrentJumpSpeed = 0;
	float m_JumpSpeed = 0;

	bool CanMove = true;
	bool IsGrounded = false;
	bool IsJumping = false;
	bool JustJumped = false;
	bool AppliedGravity = false;
	bool Moving = false;

	bool TouchingRight = false;
	bool TouchingLeft = false;
	bool TouchingUp = false;
	bool TouchingDown = false;

	Vector Velocity{ 0, 0 };
	
	float TempSpeed = 0;

	//Collision
	int VectorPosition = 0;

	float TopLeftPosX;
	float TopLeftPosY;
	float TopRightPosX;
	float TopRightPosY;
	float BotLeftPosX;
	float BotLeftPosY;
	float BotRightPosX;
	float BotRightPosY;

	//Drawing sprites
	bool FacingRight = true;




	//Size of creature
	int m_Width;
	int m_Height;


	

	

};

