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

	MaxPlayerPositionLeft = (m_ScreenWidth / 4)-128;
	MaxPlayerPositionRight = (m_ScreenWidth - (m_ScreenWidth / 4));
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

void Level::RenderLevel(float PlayerX, float PlayerY)
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

	//Makes it so m_Offset is between -64 and 64. 
	if (m_Offset > 64)
	{
		m_temp = m_Offset - 64;
		m_Offset = 0;
		m_Offset += m_temp;
		VectorPos--;
	}
	else if (m_Offset < -64)
	{
		m_temp = m_Offset + 64;
		m_Offset = 0;
		m_Offset += m_temp;
		VectorPos++;
	}
	

	m_XDrawTo += m_Offset;
	
	SavedXDrawTo = m_XDrawTo;

	m_DrawingPosition = VectorPos;
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
		//41 goes to the next block that needs to be renderered on the next line. will break if the rows are made bigger in level text file 
		m_DrawingPosition += 41;
		//m_DrawingPosition = 0;
		//m_DrawingPosition += ((i*m_ShowableWidth)+XVectorPos);
		
		m_XDrawTo = SavedXDrawTo;
		m_YDrawTo = m_YDrawTo + m_BlockHeight;
	}
	m_ViewPortPrevX = ViewPortX;
	std::cout << "m_XDrawTo is " << m_XDrawTo << std::endl;
	m_XDrawTo = -64;
	std::cout << "Offset is " << m_Offset << std::endl;
	m_YDrawTo = 0;

	//DrawBlockOnPosition(ViewPortX, ViewPortY, DirtBlock);
	
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
	//Use VectorPos to find what part of the level is rendered on screen

	//Find where the player is within the level by using the cords in the functions parameter


	TopX += m_Offset;
	BotX += m_Offset;
	//First need to find top left position
	ColXVectorPos = XVectorPos;
	ColYVectorPos = YVectorPos;
	ColVectorPos = ColVectorPos;
	VectorPositionObject = "";

	//first check if top x / y are going into a block

	//find out how many times TopX goes into 64 (64 equals the size of a block)
	while (TopX > 64) 
	{
		TopX -= 64;
		ColXVectorPos++;
	}

	//same for TopY
	while (TopY > 64) 
	{
		TopY-= 64;
		ColYVectorPos += m_LevelWidth; 
	}

	//add both results together and use that number to look in the level vector
	ColVectorPos = ColXVectorPos + ColYVectorPos;
	//std::cout << "looking in vector position " << VectorPos << "." << std::endl;
	std::cout << "top left block is" << m_GridLayout.at(ColVectorPos) << std::endl;
	//if position doesnt equal "." then there is something there so return true (meaning there's a wall there)
	if (m_GridLayout.at(ColVectorPos) != "." && m_GridLayout.at(ColVectorPos) != "P")
	{
		return true;
	}

	//else do the same for BotX and BotY
	/*ColXVectorPos = 0 + XVectorPos;
	ColYVectorPos = 0 + YVectorPos;
	ColVectorPos = 0;
	VectorPositionObject = "";
	
	while (BotX > 64)
	{
		BotX -= 64;
		ColXVectorPos++;
	}

	while (BotY > 64)
	{
		BotY -= 64;
		ColYVectorPos+= m_LevelWidth;
	}

	ColVectorPos = ColXVectorPos + ColYVectorPos;
	//std::cout << "looking in vector position " << VectorPos << "." << std::endl;

	if (m_GridLayout.at(VectorPos) != "." && m_GridLayout.at(VectorPos) != "P")
	{
		return true;
	}
	*/
	return false;
}



int Level::GetViewPortX()
{
	return ViewPortX;
}

int Level::GetMaxPlayerPositionLeft()
{
	return MaxPlayerPositionLeft;
}

int Level::GetMaxPlayerPositionRight()
{
	return MaxPlayerPositionRight;
}

