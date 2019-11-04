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

class Bitmap; //04-01

class Game
{
public:
	Game();
	~Game();
	void GameLoop();

	void Render();

	void CheckKeyPressed();

private:
	int m_ScreenWidth = 1280;
	int m_ScreenHeight = 720;


	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	Player* m_Player; //04-01
	Monster* m_Monster;
	Level* level;

	Sky* m_Sky;

	int x = 50;

	std::string Icon = "Assets/Icon.bmp";
	SDL_Surface* m_IconSurface;

	UI* ui = new UI();
	Input* input = new Input();
};

