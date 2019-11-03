#include "UI.h"

UI::UI()
{
	std::cout << "UI created!" << std::endl;
	//read in the font
	m_pSmallFont = TTF_OpenFont("Assets/DejaVuSans.ttf", 15);
	//m_pBigFont = TTF_OpenFont("Assets/DejaVuSans.ttf", 50);

}

UI::~UI()
{
	//Destroy font
	TTF_CloseFont(m_pBigFont);
	TTF_CloseFont(m_pSmallFont);


}

// Text we want to display, screen X and Y positions, font we want to use, colour of text
void UI::UpdateText(std::string msg, int x, int y, SDL_Color colour, SDL_Renderer* renderer)
{

	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	
	int texW = 0;
	int texH = 0;

	//SDL_Color color = {0, 0, 0 };

	//char msg[100]
	//sprintf_s(msg, "Checks: %d", m_checkTally);

	m_pBigFont = TTF_OpenFont("Assets/DejaVuSans.ttf", 75);
	surface = TTF_RenderText_Solid(m_pBigFont, msg.c_str(), colour);

	if (!surface)
	{
		//surface not loaded
		printf("SURFACE for font not loaded! \n");
		printf("%s\n", SDL_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (!texture)
		{
			//surface not loaded
			printf("SURFACE for font not loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect textRect = { x, y, texW, texH };

			SDL_RenderCopy(renderer, texture, NULL, &textRect);
		}

	}
	
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}

	if (surface)
	{
		SDL_FreeSurface(surface);
	}


}
