#include "Sky.h"


Sky::Sky(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture)
	:Entity(renderer, xpos, ypos, useTransparency)
{
	std::cout << "Sky created" << std::endl;

	UpdateBitmap(DefaultPicture, true);

}
