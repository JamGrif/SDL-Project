#include "Creature.h"

Creature::Creature(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture)
	:Entity(renderer, xpos, ypos, useTransparency)

{
	IdleAnimation = DefaultPicture;
	//IdleAnimation = "Assets/Player.bmp";
	//RunningAnimation = "Assets/Player - Running.bmp";
	if (IdleAnimation == "") 
	{
		IdleAnimation = "Assets/MissingTexture.bmp";
	}
	UpdateBitmap(IdleAnimation, true);
}

void Creature::MoveUp()
{
	UpdateBitmap(IdleAnimation, true);
	m_Y -= m_Speed;
}

void Creature::MoveDown()
{
	UpdateBitmap(IdleAnimation, true);
	m_Y += m_Speed;
}

void Creature::MoveLeft()
{
	Lcount++;
	if (CurrentAnimation == IdleAnimation && Lcount == 8)
	{
		Lcount = 0;
		UpdateBitmap(RunningAnimation, true);
	}
	else if (CurrentAnimation == RunningAnimation && Lcount == 8)
	{
		Lcount = 0;
		UpdateBitmap(IdleAnimation, true);
	}
	m_X -= m_Speed;

}

void Creature::MoveRight()
{
	Rcount++;
	if (CurrentAnimation == IdleAnimation && Rcount == 8)
	{
		Rcount = 0;
		UpdateBitmap(RunningAnimation, true);
	}
	else if (CurrentAnimation == RunningAnimation && Rcount == 8)
	{
		Rcount = 0;
		UpdateBitmap(IdleAnimation, true);
	}

	m_X += m_Speed;

}

void Creature::MoveJump()
{
	//to do

}
