#pragma once
#include <string>
#include "SDL.h"
#include "SDL_render.h"
#include <iostream>
#include <vector>
#include "Level.h"
struct SDL_Surface; //container for the raw pixels we want to display
struct SDL_Texture;
struct SDL_Renderer;
class Entity
{
public:
	Entity(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency);
	~Entity();

	void UpdateBitmap(std::string filename, bool useTransparency);
	virtual void draw();

	int GetX();
	int GetY();


protected:
	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

	float m_X = 0;
	float m_Y = 0;
	float m_PrevX = 0;
	float m_PrevY = 0;

	float m_DrawX = 0;

	std::string Filename = "";

	std::string CurrentAnimation = "";

	Level* levelinfo;

};

