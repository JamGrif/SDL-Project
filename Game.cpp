#include "Game.h"

Game::Game()
{
	m_Window = nullptr;
	m_Renderer = nullptr;

	//start up
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	//create the window
	//Title, initial x position, initial y position, width in pixels, height in pixels, window behaviour flags
	m_Window = SDL_CreateWindow("Game Window", 300, 300, 640, 480, 0);

	if (!m_Window) 
	{
		printf("WINDOW initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		getchar();
		return;
	}

	//now create the renderer
	//link renderer to newly created window,index rendering driver, renderer behaviour flags
	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);

	if (!m_Renderer) 
	{
		printf("RENDERER initialisation failed: %s\n", SDL_GetError());
		printf("Press any key to continue\n");
		getchar();
		return;
	}

	//read in the font
	m_pSmallFont = TTF_OpenFont("Assets/DejaVuSans.ttf", 15);
	m_pBigFont = TTF_OpenFont("Assets/DejaVuSans.ttf", 50);


	m_Player = new Player(m_Renderer, 100, 100, true, "Assets/Player.bmp");
	m_Monster = new Monster(m_Renderer, 200, 200, true, "Assets/monstertrans.bmp");

}

Game::~Game()
{
	//Destroy created bitmaps
	if (m_Player)
	{
		delete m_Player;
	}

	//Destroy font
	TTF_CloseFont(m_pBigFont);
	TTF_CloseFont(m_pSmallFont);

	//Destroy in reverse order they were created
	if (m_Renderer) 
	{
		SDL_DestroyRenderer(m_Renderer);
	}

	if (m_Window) 
	{
		SDL_DestroyWindow(m_Window);
	}
}

void Game::GameLoop()
{
	//!input->KeyIsPressed(KEY_ESCAPE)
	while (!input->KeyIsPressed(KEY_ESCAPE)) //Game ends if escape is pressed
	{
	
		CheckKeyPressed();

		m_Player->draw();

		m_Monster->draw();

		UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
		UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0,0,255 });

		char char_array[] = "Big White";
		UpdateText(char_array, 50, 140, m_pBigFont, { 255,255,255 });

		std::string myString = "Big Green";
		UpdateText(myString, 50, 70, m_pBigFont, { 0,255,0 });

		/*int testNumber = 1234;
		std::string testString = "Test Number: ";
		testString += to_string(testNumber);
		UpdateText(testString, 50, 210, m_pBigFont, { 255,255,255 });
		*/

		Render();
		SDL_Delay(16);

	}
	std::cout << "Game ended via escape" << std::endl;
	delete input;
	input = nullptr;
}


void Game::Render()
{

	//show what we've drawn
	SDL_RenderPresent(m_Renderer);

	//wipe the display to the colour we just set
	SDL_RenderClear(m_Renderer);

}

void Game::CheckKeyPressed()
{
	input->Update();
	//Keyboard
	if (input->KeyIsPressed(KEY_D))
	{
		m_Player->MoveRight();
	}
	if (input->KeyIsPressed(KEY_A))
	{
		m_Player->MoveLeft();
	}
	if (input->KeyIsPressed(KEY_W)) 
	{
		m_Player->MoveUp();
	}
	if (input->KeyIsPressed(KEY_S))
	{
		m_Player->MoveDown();
	}
	if (input->KeyIsPressed(KEY_SPACE))
	{
		m_Player->MoveJump();
		std::cout << "Space key is pressed!" << std::endl;
	}
	if (input->KeyIsPressed(KEY_R)) 
	{
		std::cout << "R key is pressed!" << std::endl;
	}
	//Mouse
	if (input->MouseIsPressed(MOUSE_LEFT)) 
	{
		std::cout << "Mouse X position is " << input->GetMouseX() << ". Mouse Y position is " << input->GetMouseY() << "." << std::endl;
	}
	if (input->MouseIsPressed(MOUSE_RIGHT))
	{
		std::cout << "Right mouse is pressed!" << std::endl;
	}
	if (input->MouseIsPressed(MOUSE_MIDDLE))
	{
		std::cout << "Middle mouse is pressed!" << std::endl;
	}


}

// Text we want to display, screen X and Y positions, font we want to use, colour of text
void Game::UpdateText(std::string msg, int x, int y, TTF_Font* font, SDL_Color colour)
{
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	int texW = 0;
	int texH = 0;

	//SDL_Color color = {0, 0, 0 };

	//char msg[100]
	//sprintf_s(msg, "Checks: %d", m_checkTally);

	surface = TTF_RenderText_Solid(font, msg.c_str(), colour);
	if (!surface) 
	{
		//surface not loaded
		printf("SURFACE for font not loaded! \n");
		printf("%s\n", SDL_GetError());
	}
	else 
	{
		texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		if (!texture) 
		{
			//surface not loaded
			printf("SURFACE for font not loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else 
		{
			SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
			SDL_Rect textRect = { x, y, texW, texH };

			SDL_RenderCopy(m_Renderer, texture, NULL, &textRect);
		}

	}

	if (texture) 
	{
		SDL_DestroyTexture(texture);
	}

	if (surface) 
	{
		SDL_FreeSurface(surface);
	}



}

