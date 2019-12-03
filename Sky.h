#pragma once
#include "Entity.h"
class Sky :
	public Entity
{
public:
	Sky(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency);

	void draw();

private:
	std::string SkyBitmap = "Assets/Sky.bmp";


};

