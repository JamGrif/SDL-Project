#pragma once
#include <SDL.h>
#include <string>
#include "SDL_ttf.h"
#include <iostream>
class UI
{
public:
	UI();
	~UI();

	void UpdateText(std::string msg, int x, int y, SDL_Color colour, SDL_Renderer* renderer);

	//TTF_Font* font

private:

	TTF_Font* m_pSmallFont;
	TTF_Font* m_pBigFont = TTF_OpenFont("Assets/DejaVuSans.ttf", 50);


};

