#include "Game.h"

Game::Game()
{
	m_Window = nullptr;
	m_Renderer = nullptr;

	//start up
	SDL_Init(SDL_INIT_VIDEO);

	//create the window
	//Title, initial x position, initial y position, width in pixels, height in pixels, window behaviour flags
	m_Window = SDL_CreateWindow("Game Window", 300, 300, 1280, 720, 0);

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

	m_Player = new Bitmap(m_Renderer, "Assets/Player.bmp", 100, 100, true);
	

}

Game::~Game()
{
	//Destroy created bitmaps
	if (m_Player)
	{
		delete m_Player;
	}

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

		Render();
		SDL_Delay(16);

	}
	std::cout << "Game ended via escape" << std::endl;
	delete input;
	input = nullptr;
}


void Game::Render()
{
	//wipe the display to the colour we just set
	//SDL_RenderClear(m_Renderer);

	//show what we've drawn
	SDL_RenderPresent(m_Renderer);

}

void Game::CheckKeyPressed()
{
	input->Update();
	if (input->KeyIsPressed(KEY_D))
	{
		std::cout << "D key pressed!" << std::endl;
	}
	if (input->KeyIsPressed(KEY_A))
	{
		std::cout << "A key pressed!" << std::endl;
	}
	if (input->KeyIsPressed(KEY_SPACE))
	{
		std::cout << "Space key is pressed!" << std::endl;
	}

}

