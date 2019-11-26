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
	void RenderLevel(float PlayerX, float PlayerY);
	void DrawBlockOnPosition(int X, int Y, std::string Asset, bool UseTransparency = false);


	bool IsWall(int TopX, int TopY, int BotX, int BotY);


	int GetViewPortX();

	//int GetMaxPlayerPositionLeft();
	//int GetMaxPlayerPositionRight();

private:
	int coltemp = 0;
	//Size of each block
	const int m_BlockWidth = 64;
	const int m_BlockHeight = 64;

	//Size of the currently loaded level in block amounts
	int m_LevelWidth;
	int m_LevelHeight;

	//This is how many blocks can be shown on the screen at once
	const int MaxBlockWidth = 22;
	const int MaxBlockHeight = 12;

	//Variables used to draw the level 
	int SavedXDrawTo = 0;
	int m_XDrawTo = -64;
	int m_YDrawTo = 0;
	int m_DrawingPosition;

	int m_Offset = 0;
	int m_tempOffset = 0;

	//Used to find what part of the vector needs to be drawn
	//int XVectorPos = 0;
	//int YVectorPos = 0;
	int VectorPos = 0;

	bool CanLevelMove;

	
	//int MaxPlayerPositionLeft = 0;
	//int MaxPlayerPositionRight = 0;

	//Used to convert from world space to screen space
	int ViewPortX = 0;
	int ViewPortY = 0;

	int m_ViewPortPrevX;

	int MaxViewPortX = 0;
	int MaxViewPortY = 0;

	//Currently loaded level in the vector
	int m_LoadedLevel = 0;

	//Collision to look inside the level vector
	int ColXVectorPos = 0;
	int ColYVectorPos = 0;
	int ColVectorPos = 0;

	std::string VectorPositionObject = "";

	//Size of game window
	int m_ScreenWidth, m_ScreenHeight;

	//SDL stuff
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pbitmap;
	SDL_Surface* m_psurface;

	//Blocks to draw
	std::string GrassBlock = "Assets/GrassBlock.bmp";
	std::string DirtBlock = "Assets/DirtBlock.bmp";
	std::string StoneBlock = "Assets/StoneBlock.bmp";
	std::string PlayerSpawn = "Assets/PlayerSpawn.bmp";
	std::string CoalBlock = "Assets/CoalBlock.bmp";

	//The level vector
	std::vector<std::string> m_GridLayout;
	

};

