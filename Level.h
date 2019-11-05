#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_render.h"


class Level
{
public:
	Level(SDL_Renderer* renderer, int ScreenWidth, int ScreenHeight);
	~Level();

	void LoadLevel(int LevelToLoad);
	void RenderLevel();
	void DrawBlockOnPosition(int X, int Y, std::string Asset);

	bool IsWall(int TopX, int TopY, int BotX, int BotY);

private:
	int m_BlockWidth = 64;
	int m_BlockHeight = 64;

	int m_LevelWidth;
	int m_LevelHeight;

	int m_XDrawTo = 0;
	int m_YDrawTo = 0;
	int m_DrawingPosition;

	int m_LoadedLevel = 0;

	int m_ScreenWidth, m_ScreenHeight;

	Uint32 BlockColour = NULL;

	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pbitmap;
	SDL_Surface* m_psurface;

	std::string GrassBlock = "Assets/GrassBlock.bmp";
	std::string DirtBlock = "Assets/DirtBlock.bmp";
	std::string StoneBlock = "Assets/StoneBlock.bmp";

	std::vector<std::string> m_GridLayout;
	
	//char m_GridLayout[m_LevelWidth][m_LevelHeight];

};

