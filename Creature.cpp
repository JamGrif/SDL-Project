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
	m_Y -= m_Speed;
}

void Creature::MoveDown()
{
	m_Y += m_Speed;
}

void Creature::MoveLeft()
{
	m_X -= m_Speed;
}

void Creature::MoveRight()
{
	m_X += m_Speed;
}

void Creature::MoveJump()
{
	//to do

}
