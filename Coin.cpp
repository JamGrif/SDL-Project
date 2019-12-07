#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency)
	:Entity(renderer, xpos, ypos, pLevel, useTransparency)
{
	CurrentPicture = "Assets/Coin.bmp";
	UpdateBitmap(CurrentPicture, useTransparency);

	//Position.x = xpos;
	//Position.y = ypos;

	m_Width = 32;
	m_Height = 32;

}

void Coin::Update(int PlayerX, int PlayerY)
{
	//std::cout << "Coin updated!" << std::endl;

	//Check for collision with player
	GetCollisionPosition();
	
	if (PlayerX > TopLeftPosX && PlayerX < TopRightPosX && PlayerY > TopLeftPosY && PlayerY < BotRightPosY)
	{
		//std::cout << "Player collided with coin" << std::endl;
		CoinCollected = true;
		Position.y = -50;
	}
	




	//Update sprite




}

int Coin::IsCoinCollected()
{
	if (CoinCollected && !AppliedCoinAddition) 
	{
		AppliedCoinAddition = true;
		return CoinCollected;
	}
	
}
