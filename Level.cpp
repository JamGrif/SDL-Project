#include "Level.h"

Level::Level(SDL_Renderer* renderer, int ScreenWidth, int ScreenHeight)
{
	//Screen resoultion fits a width of 20 blocks and a height of 12 blocks
	m_pRenderer = renderer;
	m_ScreenWidth = ScreenWidth;
	m_ScreenHeight = ScreenHeight;

	MaxViewPortX = ScreenWidth;
	MaxViewPortY = ScreenHeight;

	//By default, the program loads level 1 first
	LoadLevel(1);

}

Level::~Level()
{
	m_GridLayout.clear();
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
				else if (ThingToAdd.at(0) == 'P') 
				{
					m_GridLayout.push_back("P");
				}
				else if (ThingToAdd.at(0) == 'C')
				{
					m_GridLayout.push_back("C");
				}
				else //If program isnt sure whats in text position or there is a "." in position then adds empty space
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

void Level::RenderLevel(int PlayerX, int PlayerY)
{
	
	//Find the top left position of the screen with regards to the players world position. The level isn't changed on the Y-axis so only the X is needed

	ViewPortX = PlayerX - (m_ScreenWidth/2);
	
	//Find if player moved right or left by comparing m_PlayerPrevX with PlayerX

	if (ViewPortX < m_ViewPortPrevX) //Player moved left 
	{
		m_Offset += (m_ViewPortPrevX - ViewPortX);

	}
	else if (ViewPortX > m_ViewPortPrevX) //Player moved right 
	{
		m_Offset -= (ViewPortX - m_ViewPortPrevX);
	}

	//Makes it so m_Offset is always -64 and 64. Raises / reduces number if exceeds

	if (m_Offset > m_BlockWidth)
	{
		m_tempOffset = m_Offset - m_BlockWidth;
		m_Offset = 0;
		m_Offset += m_tempOffset;
		VectorPos--;
	}
	else if (m_Offset < -m_BlockWidth)
	{
		m_tempOffset = m_Offset + m_BlockWidth;
		m_Offset = 0;
		m_Offset += m_tempOffset;
		VectorPos++;
	}
	
	//Set all the variables used for drawing level

	m_XDrawTo += m_Offset;
	SavedXDrawTo = m_XDrawTo;
	m_DrawingPosition = VectorPos;
	coltemp = m_XDrawTo;

	//Loop to draw the level

	for (int i = VectorPos; i < VectorPos + MaxBlockHeight; i++)
	{
		for (int j = VectorPos; j < VectorPos + MaxBlockWidth; j++)
		{
			if (m_GridLayout.at(m_DrawingPosition) == "G") //Grass block
			{
				DrawBlockOnPosition(m_XDrawTo, m_YDrawTo, GrassBlock);
			}
			else if (m_GridLayout.at(m_DrawingPosition) == "D") //Dirt block
			{
				DrawBlockOnPosition(m_XDrawTo, m_YDrawTo, DirtBlock);
			}
			else if (m_GridLayout.at(m_DrawingPosition) == "S") //Stone block
			{
				DrawBlockOnPosition(m_XDrawTo, m_YDrawTo, StoneBlock);
			}
			else if (m_GridLayout.at(m_DrawingPosition) == "P") //Player spawn 
			{
				DrawBlockOnPosition(m_XDrawTo, m_YDrawTo, PlayerSpawn, true);
			}
			else if (m_GridLayout.at(m_DrawingPosition) == "C") //Coal Block
			{
				DrawBlockOnPosition(m_XDrawTo, m_YDrawTo, CoalBlock);
			}
			else //Empty space
			{

			}
			
			m_XDrawTo += m_BlockWidth;
			m_DrawingPosition++;
		}

		//NEED TO FIX BELOW SO NUMBER IS WORKED OUT AUTOMATICALLY <------------------------------------------------------------
		//70 goes to the next block that needs to be renderered on the next line. will break if the rows are made bigger in level text file 
		m_DrawingPosition += 70;
		
		m_XDrawTo = SavedXDrawTo;
		m_YDrawTo = m_YDrawTo + m_BlockHeight;
	}

	//Reset everything ready for next render of level

	m_ViewPortPrevX = ViewPortX;
	m_XDrawTo = -m_BlockWidth;
	m_YDrawTo = 0;
	
}

void Level::DrawBlockOnPosition(int X, int Y, std::string Asset, bool UseTransparency)
{
	
	//Create the surface
	m_psurface = SDL_LoadBMP(Asset.c_str());

	if (UseTransparency)
	{
		Uint32 colourKey = SDL_MapRGB(m_psurface->format, 255, 0, 255);
		SDL_SetColorKey(m_psurface, SDL_TRUE, colourKey);
	}

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
	//Find where the player is within the level by using the cords in the functions parameter
	//The X cords are adjusted for the offset used to draw the level and the players viewport
	TopX -= ((ViewPortX + m_Offset) - m_BlockWidth);
	BotX -= ((ViewPortX + m_Offset) - m_BlockWidth);

	//ColVectorPos is the top left block within the vector
	ColXVectorPos = 0;
	ColYVectorPos = 0;
	ColVectorPos = VectorPos;

	//As the top left block is known we can find out where the player is within the vector
	//Find out how many times TopX goes into 64 (64 equals the size of a block)
	while (TopX > m_BlockWidth)
	{
		TopX -= m_BlockWidth;
		ColXVectorPos++;
	}

	//Same for TopY
	while (TopY > m_BlockWidth)
	{
		TopY -= m_BlockWidth;
		ColYVectorPos += m_LevelWidth; 
	}

	//Can add ColXVector & and ColYVector to ColVectorPos to find out exactly where this creature is
	ColVectorPos += ColXVectorPos + ColYVectorPos;
	
	//if position doesnt equal "." then there is something there so return true (meaning there's a wall there)
	if (m_GridLayout.at(ColVectorPos) != "." && m_GridLayout.at(ColVectorPos) != "P")
	{
		return true;
	}

	//If TopX&Y didn't hit anything then BotX&Y will be checked

	ColXVectorPos = 0;
	ColYVectorPos = 0;
	ColVectorPos = VectorPos;


	while (BotX > m_BlockWidth)
	{
		BotX -= m_BlockWidth;
		ColXVectorPos++;
	}

	while (BotY > m_BlockWidth)
	{
		BotY -= m_BlockWidth;
		ColYVectorPos += m_LevelWidth;
	}

	ColVectorPos += ColXVectorPos + ColYVectorPos;

	if (m_GridLayout.at(ColVectorPos) != "." && m_GridLayout.at(ColVectorPos) != "P")
	{
		return true;
	}
	return false;
}



int Level::GetViewPortX()
{
	return ViewPortX;
}

/*int Level::GetMaxPlayerPositionLeft()
{
	return MaxPlayerPositionLeft;
}

int Level::GetMaxPlayerPositionRight()
{
	return MaxPlayerPositionRight;
}*/

