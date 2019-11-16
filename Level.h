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
	void RenderLevel(int PlayerX, int PlayerY);
	void DrawBlockOnPosition(int X, int Y, std::string Asset, bool UseTransparency = false);

	bool IsWall(int TopX, int TopY, int BotX, int BotY);


	int GetPlayerSpawnX();
	int GetPlayerSpawnY();

private:
	int m_BlockWidth = 64;
	int m_BlockHeight = 64;

	int m_LevelWidth;
	int m_LevelHeight;

	int m_ShowableWidth = 20;
	int m_ShowableHeight = 12;

	//This is how many blocks can be shown on the screen at once
	const int MaxBlockWidth = 20;
	const int MaxBlockHeight = 12;

	int m_XDrawTo = 0;
	int m_YDrawTo = 0;
	int m_DrawingPosition;

	int m_LoadedLevel = 0;

	int PlayerSpawnX = 0;
	int PlayerSpawnY = 0;

	int ViewPortX = 0;
	int ViewPortY = 0;

	int MaxViewPortX = 0;
	int MaxViewPortY = 0;

	//Collision
	int XVectorPos = 0;
	int YVectorPos = 0;
	int VectorPos = 0;
	std::string VectorPositionObject = "";

	int m_ScreenWidth, m_ScreenHeight;

	Uint32 BlockColour = NULL;

	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pbitmap;
	SDL_Surface* m_psurface;

	std::string GrassBlock = "Assets/GrassBlock.bmp";
	std::string DirtBlock = "Assets/DirtBlock.bmp";
	std::string StoneBlock = "Assets/StoneBlock.bmp";
	std::string PlayerSpawn = "Assets/PlayerSpawn.bmp";
	std::string CoalBlock = "Assets/CoalBlock.bmp";

	std::vector<std::string> m_GridLayout;
	
	//char m_GridLayout[m_LevelWidth][m_LevelHeight];

};

