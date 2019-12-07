#pragma once
#include <string>
#include "SDL.h"
#include "SDL_render.h"
#include <iostream>
#include <vector>
#include "Level.h"

class Entity
{
public:
	Entity(SDL_Renderer* renderer, int xpos, int ypos, Level* pLevel, bool useTransparency = true);
	~Entity();

	void UpdateBitmap(std::string filename, bool useTransparency);
	virtual void draw();

	void GetCollisionPosition();

	int GetX();
	int GetY();

	//virtual void Update() = 0;
	

protected:
	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

	struct Vector { int x; int y; };
	Vector Position = { 0,0 };
	Vector Velocity{ 0, 0 };

	//float m_X = 0;
	//float m_Y = 0;
	int m_PrevX = 0;
	int m_PrevY = 0;

	int m_DrawX = 0;

	std::string Filename = "";

	std::string CurrentPicture = "";

	Level* levelinfo;

	int TopLeftPosX = 0;
	int TopLeftPosY = 0;
	int TopRightPosX = 0;
	int TopRightPosY = 0;
	int BotLeftPosX = 0;
	int BotLeftPosY = 0;
	int BotRightPosX = 0;
	int BotRightPosY = 0;

	//Size of Entity
	int m_Width = 0;
	int m_Height = 0;


};

