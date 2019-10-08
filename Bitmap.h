#pragma once
#include <string>
#include "SDL.h"
#include "SDL_render.h"
struct SDL_Surface; //container for the raw pixels we want to display
struct SDL_Texture;
struct SDL_Renderer;
class Bitmap
{
public:
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = false);
	~Bitmap();

	void draw();


private:
	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

	int m_X = 0;
	int m_Y = 0;


};

