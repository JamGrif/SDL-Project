#include "Sky.h"


Sky::Sky(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency)
	:Entity(renderer, xpos, ypos, pLevel, useTransparency)
{
	std::cout << "Sky created" << std::endl;

	UpdateBitmap(SkyBitmap, true);

}

void Sky::draw()
{
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { Position.x-1, Position.y - 1, m_pbitmapSurface->w, m_pbitmapSurface->h }; //Where on screen bitmap is drawn to and how big it will appear
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
}
