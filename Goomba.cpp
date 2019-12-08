#include "Goomba.h"

Goomba::Goomba(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, Player* pPlayer, bool useTransparency)
	:Creature(renderer, xpos, ypos, pLevel, useTransparency)
{
	m_Width = 48;
	m_Height = 48;

	UpdateBitmap(GoombaSprite, true);
	
	playerinfo = pPlayer;

	m_Acceleration = 1;
}

void Goomba::Update()
{
	PlayerX = playerinfo->GetX();

	//Only updates Goomba if within range of player
	if (PlayerX < Position.x + 1000 && PlayerX > Position.x - 1000) 
	{
		//Check if goomba can move in direction
		GetCollisionPosition();

		if (MovingRight) //Check to the right of the goomba for a wall
		{
			MovingRight = levelinfo->IsWall(TopRightPosX, TopRightPosY, BotRightPosX, BotRightPosY - 2) == true ? false : true;
		}
		else //Check to the left of the goomba for a wall
		{
			MovingRight = levelinfo->IsWall(TopLeftPosX, TopLeftPosY, BotLeftPosX, BotLeftPosY - 2) == true ? true : false;
		}

		//Move goomba in a direction
		if (MovingRight) //Move the goomba to the right
		{
			Position.x += 1;
		}
		else //Move the goomba to the left
		{
			Position.x -= 1;
		}
	}
	


}

