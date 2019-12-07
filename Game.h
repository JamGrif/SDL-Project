#pragma once
#include <SDL.h>
#include "Input.h"
#include <stdio.h>
#include <iostream>
#include "Player.h"
#include "Monster.h"
#include <string>
#include "SDL_ttf.h"
#include "UI.h"
#include "Sky.h"
#include "Level.h"
#include "conio.h"
#include "Coin.h"

//class Bitmap; //04-01

class Game
{
public:
	Game();
	~Game();
	void GameLoop();

	void Render();

	void CheckKeyPressed();

	/*struct Clock 
	{
		uint32_t last_tick_time = 0;
		uint32_t delta = 0;

		void tick()
		{
			uint32_t tick_time = SDL_GetTicks();
			delta = tick_time - last_tick_time;
			last_tick_time = tick_time;
		}
	};*/

	

private:
	int m_ScreenWidth = 1280;
	int m_ScreenHeight = 720;


	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	Player* m_Player; 
	Monster* m_Monster;
	Level* level;
	Coin* m_Coin;

	Sky* m_Sky;

	std::string Icon = "Assets/Icon.bmp";
	SDL_Surface* m_IconSurface;

	UI* m_ui;
	
	Input* input = new Input();
};

