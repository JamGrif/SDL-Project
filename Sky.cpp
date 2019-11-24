#include "Sky.h"


Sky::Sky(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency, std::string DefaultPicture)
	:Entity(renderer, xpos, ypos, pLevel, useTransparency)
{
	std::cout << "Sky created" << std::endl;

	UpdateBitmap(DefaultPicture, true);

}

void Sky::draw()
{
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { m_X-1, m_Y - 1, m_pbitmapSurface->w, m_pbitmapSurface->h }; //Where on screen bitmap is drawn to and how big it will appear
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
}
