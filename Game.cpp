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
	m_Window = SDL_CreateWindow("Super Minecraft Bros", 200, 200, m_ScreenWidth, m_ScreenHeight, 0);

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

	m_IconSurface = SDL_LoadBMP(Icon.c_str());
	SDL_SetWindowIcon(m_Window, m_IconSurface);

	level = new Level(m_Renderer, m_ScreenHeight, m_ScreenWidth);

	m_Player = new Player(m_Renderer, m_ScreenWidth/2, m_ScreenHeight/2-128, level);

	m_Sky = new Sky(m_Renderer, 0, 0, level);

	m_ui = new UI(m_Renderer);

	ListOfCoins.push_back(m_Coin1 = new Coin(m_Renderer, 1800, 525, level));
	ListOfCoins.push_back(m_Coin2 = new Coin(m_Renderer, 625, 525, level));
	ListOfCoins.push_back(m_Coin3 = new Coin(m_Renderer, 2410, 450, level));
	ListOfCoins.push_back(m_Coin4 = new Coin(m_Renderer, 3190, 330, level));
	ListOfCoins.push_back(m_Coin5 = new Coin(m_Renderer, 4275, 390, level));

}

Game::~Game()
{
	//Destroy created bitmaps
	if (m_Player)
	{
		delete m_Player;
	}

	delete level;
	delete input;
	delete m_ui;

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

	while (m_Player->HasPlayerWon() == false) //Game ends if escape is pressed 
	{
		
		CheckKeyPressed();

		//Calculations and updating stuff
		m_Player->Update();

		//Drawing stuff
		m_Sky->draw();
		
		
		level->RenderLevel(m_Player->GetX(),m_Player->GetY());
		m_Player->draw();

		for (auto coin : ListOfCoins)
		{
			coin->Update(m_Player->GetX(), m_Player->GetY());
			coin->draw();
			if (coin->IsCoinCollected() == true)
			{
				m_Player->IncreaseCoinsCollected();
			}
		}

		m_ui->PresentUi(m_Player->GetCoinsCollected());
		

		//Render stuff
		Render();
		SDL_Delay(16);

	}

	std::cout << "Game ended, player won!" << std::endl;
	delete input;
	delete m_ui;
	input = nullptr;
	m_ui = nullptr;
}


void Game::Render()
{
	//show what was drawn
	SDL_RenderPresent(m_Renderer);

	//wipe the display 
	SDL_RenderClear(m_Renderer);

}

void Game::CheckKeyPressed()
{
	input->Update();
	//Keyboard
	if (input->KeyIsPressed(KEY_D))
	{
		m_Player->Move('r');
	}
	if (input->KeyIsPressed(KEY_A))
	{
		m_Player->Move('l');
	}
	if (input->KeyIsPressed(KEY_W)) 
	{
		m_Player->Move('u');
	}
	if (input->KeyIsPressed(KEY_S))
	{
		m_Player->Move('d');
	}
	if (input->KeyIsPressed(KEY_SPACE))
	{
		m_Player->Move('j');
		//std::cout << "Space key is pressed!" << std::endl;
	}
	if (input->KeyIsPressed(KEY_R)) 
	{
		//std::cout << "R key is pressed!" << std::endl;
		m_Player->DisplayPosition();
	}
	if (input->KeyIsPressed(KEY_1))
	{
	}
	if (input->KeyIsPressed(KEY_2))
	{
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



