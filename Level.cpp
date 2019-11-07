#include "Level.h"

Level::Level(SDL_Renderer* renderer, int ScreenWidth, int ScreenHeight)
{
	//Screen resoultion fits a width of 20 blocks and a height of 12 blocks
	m_pRenderer = renderer;
	m_ScreenWidth = ScreenWidth;
	m_ScreenHeight = ScreenHeight;

	//By default, the program loads level 1 first
	LoadLevel(1);
}

Level::~Level()
{

}


void Level::LoadLevel(int LevelToLoad)
{
	
	if (LevelToLoad != m_LoadedLevel) 
	{
		std::cout << "loading level " << LevelToLoad << std::endl;
		m_LoadedLevel = LevelToLoad;

		if (m_GridLayout.empty() == false) //If level is already in vector then clear the vector for next level
		{
			m_GridLayout.clear();
		}

		std::string Level = "Assets/Level" + std::to_string(LevelToLoad) + ".txt";

		std::string ThingToAdd;
		std::string temp;
		int ReadingPosition = 0;

		//Open selected levels text file
		std::ifstream SaveLevelFromText;
		SaveLevelFromText.open(Level);

		if (SaveLevelFromText.fail())
		{
			std::cout << "Failed to open text file, reset program." << std::endl;
			exit(0);
		}

		//Get level width. Get first line of level and count characters
		SaveLevelFromText.seekg(0) >> temp;
		m_LevelWidth = temp.length();

		//Get level height. Get how many lines in textfile
		/*while (getline(SaveLevelFromText, temp))
		{
			m_LevelHeight++;
		}*/
		m_LevelHeight = 12;

		//Goes through the level text file and adds that character into a vector which is used for drawing
		for (int j = 0; j < m_LevelHeight; j++)
		{
			for (int i = 0; i < m_LevelWidth; i++)
			{
				SaveLevelFromText.seekg(ReadingPosition) >> ThingToAdd;
				if (ThingToAdd.at(0) == 'G')
				{
					m_GridLayout.push_back("G");
				}
				else if (ThingToAdd.at(0) == 'D')
				{
					m_GridLayout.push_back("D");
				}
				else if (ThingToAdd.at(0) == 'S')
				{
					m_GridLayout.push_back("S");
				}
				else //If program isnt sure whats in text position then adds empty space
				{
					m_GridLayout.push_back(".");
				}
				ReadingPosition++;
			}
			ReadingPosition = ReadingPosition + 2;
		}
		SaveLevelFromText.close();

	}
	
	
	
	
}

void Level::RenderLevel()
{
	m_DrawingPosition = 0;
	m_XDrawTo = 0;
	m_YDrawTo = 0;
	
	for (int i = 0; i < m_LevelHeight; i++) 
	{
		for (int j = 0; j < m_LevelWidth; j++)
		{
			if (m_GridLayout.at(m_DrawingPosition) == "G") //Grass block
			{
				DrawBlockOnPosition(m_XDrawTo, m_YDrawTo, GrassBlock);
			}
			else if (m_GridLayout.at(m_DrawingPosition) == "D") //Dirt block
			{
				DrawBlockOnPosition(m_XDrawTo, m_YDrawTo, DirtBlock);
			}
			else if (m_GridLayout.at(m_DrawingPosition) == "S") //Dirt block
			{
				DrawBlockOnPosition(m_XDrawTo, m_YDrawTo, StoneBlock);
			}
			else //Empty space
			{

			}
			m_XDrawTo = m_XDrawTo + 64;
			m_DrawingPosition++;
		}

		m_XDrawTo = 0;
		m_YDrawTo = m_YDrawTo + 64;
	}
}

void Level::DrawBlockOnPosition(int X, int Y, std::string Asset)
{
	//Create the surface
	m_psurface = SDL_LoadBMP(Asset.c_str());

	//Create the bitmap texture
	m_pbitmap = SDL_CreateTextureFromSurface(m_pRenderer, m_psurface);

	//Draw the block
	SDL_Rect destRect = { X,Y,m_BlockWidth,m_BlockHeight };
	SDL_RenderCopy(m_pRenderer, m_pbitmap, NULL, &destRect);

	//Cleanup
	SDL_DestroyTexture(m_pbitmap);
	SDL_FreeSurface(m_psurface);
	
}

bool Level::IsWall(int TopX, int TopY, int BotX, int BotY) 
{
	XVectorPos = 0;
	YVectorPos = 0;
	VectorPos = 0;
	VectorPositionObject = "";

	//first check if top x / y are going into a block

	//find out how many times TopX goes into 64 (64 equals the size of a block)
	while (TopX > 64) 
	{
		TopX -= 64;
		XVectorPos++;
	}

	//same for TopY
	while (TopY > 64) 
	{
		TopY-= 64;
		YVectorPos += 20; //20 blocks are visable in each row so adding 20 goes to the next line on screen
	}

	//add both results together and use that number to look in the level vector
	VectorPos = XVectorPos + YVectorPos;
	//std::cout << "looking in vector position " << VectorPos << "." << std::endl;

	//if position doesnt equal "." then there is something there so return true (meaning there's a wall there)
	if (m_GridLayout.at(VectorPos) != ".")
	{
		return true;
	}

	//else do the same for BotX and BotY
	XVectorPos = 0;
	YVectorPos = 0;
	VectorPos = 0;
	VectorPositionObject = "";
	
	while (BotX > 64)
	{
		BotX -= 64;
		XVectorPos++;
	}

	while (BotY > 64)
	{
		BotY -= 64;
		YVectorPos+= 20;
	}

	VectorPos = XVectorPos + YVectorPos;
	//std::cout << "looking in vector position " << VectorPos << "." << std::endl;

	if (m_GridLayout.at(VectorPos) != ".")
	{
		return true;
	}

	return false;
}

