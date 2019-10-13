#pragma once
#include <SDL.h>
#include "Input.h"
#include <stdio.h>
#include <iostream>
#include "Player.h"
#include "Monster.h"
#include <string>
#include "SDL_ttf.h"
class Bitmap; //04-01

class Game
{
public:
	Game();
	~Game();
	void GameLoop();

	void Render();

	void CheckKeyPressed();
	void UpdateText(std::string msg, int x, int y, TTF_Font* font, SDL_Color colour);

private:

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	Player* m_Player; //04-01
	Monster* m_Monster;


	TTF_Font* m_pSmallFont;
	TTF_Font* m_pBigFont;




	Input* input = new Input();
};

