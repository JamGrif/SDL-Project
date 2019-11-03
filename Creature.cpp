#include "Creature.h"

Creature::Creature(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture)
	:Entity(renderer, xpos, ypos, useTransparency)

{
	IdleAnimation = DefaultPicture;

	if (IdleAnimation == "") 
	{
		IdleAnimation = "Assets/MissingTexture.bmp";
	}
	UpdateBitmap(IdleAnimation, true);
}

void Creature::MoveUp()
{
	AnimationCount++;
	if (CurrentAnimation == IdleAnimation && AnimationCount == 8)
	{
		AnimationCount = 0;
		//UpdateBitmap(RunningAnimation, true);
	}
	else if (CurrentAnimation == RunningAnimation && AnimationCount == 8)
	{
		AnimationCount = 0;
		//UpdateBitmap(IdleAnimation, true);
	}
	m_Y -= m_Speed;

}

void Creature::MoveDown()
{
	AnimationCount++;
	if (CurrentAnimation == IdleAnimation && AnimationCount == 8)
	{
		AnimationCount = 0;
		//UpdateBitmap(RunningAnimation, true);
	}
	else if (CurrentAnimation == RunningAnimation && AnimationCount == 8)
	{
		AnimationCount = 0;
		//UpdateBitmap(IdleAnimation, true);
	}
	m_Y += m_Speed;

}

void Creature::MoveLeft()
{
	AnimationCount++;
	if (CurrentAnimation == IdleAnimation && AnimationCount == 8)
	{
		AnimationCount = 0;
		//UpdateBitmap(RunningAnimation, true);
	}
	else if (CurrentAnimation == RunningAnimation && AnimationCount == 8)
	{
		AnimationCount = 0;
		//UpdateBitmap(IdleAnimation, true);
	}
	m_X -= m_Speed;

}

void Creature::MoveRight()
{
	AnimationCount++;
	if (CurrentAnimation == IdleAnimation && AnimationCount == 8)
	{
		AnimationCount = 0;
		//UpdateBitmap(RunningAnimation, true);
	}
	else if (CurrentAnimation == RunningAnimation && AnimationCount == 8)
	{
		AnimationCount = 0;
		//UpdateBitmap(IdleAnimation, true);
	}
	m_X += m_Speed;

}

void Creature::MoveJump()
{
	//to do

}
