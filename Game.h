#pragma once
#include <SDL.h>
#include "Input.h"
#include <stdio.h>
#include <iostream>
#include "Bitmap.h"
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

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	Bitmap* m_Player; //04-01
	

	Input* input = new Input();
};

