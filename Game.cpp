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
	m_Window = SDL_CreateWindow("Game Window", 200, 200, m_ScreenWidth, m_ScreenHeight, 0);

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


	m_Player = new Player(m_Renderer, m_ScreenWidth/2, m_ScreenHeight/2, true, "Assets/Player.bmp");
	m_Monster = new Monster(m_Renderer, 400, 700, true, "Assets/Monster.bmp");


}

Game::~Game()
{
	//Destroy created bitmaps
	if (m_Player)
	{
		delete m_Player;
	}

	delete input;
	delete ui;


	

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

		m_Monster->Chase(m_Player->GetX(), m_Player->GetY());


		m_Player->draw();

		m_Monster->draw();

		/*UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
		UpdateText("Small Blue", 50, 40, m_pSmallFont, { 0,0,255 });

		char char_array[] = "Big White";
		UpdateText(char_array, 50, 140, m_pBigFont, { 255,255,255 });

		std::string myString = "Big Green";
		UpdateText(myString, 50, 70, m_pBigFont, { 0,255,0 });

		int testNumber = 1234;
		std::string testString = "Test Number: ";
		testString += to_string(testNumber);
		UpdateText(testString, 50, 210, m_pBigFont, { 255,255,255 });
		*/

		//ui->UpdateText("Run from the monster!", 40, 410, { 255,255,255 }, m_Renderer);

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



