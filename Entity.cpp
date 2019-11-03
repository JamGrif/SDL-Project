#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency)
{
	//Store the renderer for future configuring and drawing
	m_pRenderer = renderer;

	m_X = xpos;
	m_Y = ypos;
}

Entity::~Entity()
{
	if (m_pbitmapTexture)
	{
		SDL_DestroyTexture(m_pbitmapTexture);
	}
	if (m_pbitmapSurface)
	{
		SDL_FreeSurface(m_pbitmapSurface);
	}

}

void Entity::UpdateBitmap(std::string filename, bool useTransparency)
{
	//Create the bitmap surface
	m_pbitmapSurface = SDL_LoadBMP(filename.c_str()); //loads bitmap from file into a member variable

	CurrentAnimation = filename;

	if (!m_pbitmapSurface)
	{
		//bitmap failed to load
		printf("Surface for bitmap '%s' not loaded! \n", filename.c_str());
		printf("%s\n", SDL_GetError());
	}
	else
	{
		//if we are to use transparency, going to assume
		//the colour key is magenta
		if (useTransparency)
		{
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
		}

		//create the texture
		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface); //Converting raw pixels to something more efficient. Copies pixel data from one memory location to another
		if (!m_pbitmapTexture)
		{
			//texture failed to load
			printf("Texture for bitmap '%s' not loaded! a\n", filename.c_str());
			printf("%s\n", SDL_GetError());
		}
	}



}

void Entity::draw()
{
	if (m_pbitmapTexture)
	{
		SDL_Rect destRect = { m_X, m_Y, m_pbitmapSurface->w, m_pbitmapSurface->h }; //Where on screen bitmap is drawn to and how big it will appear
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
	
}


int Entity::GetX()
{
	return m_X;
}

int Entity::GetY()
{
	return m_Y;
}
