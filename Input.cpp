#include "Input.h"

Input::Input()
{
	for (int i = 0; i < SIZE_OF_KEYS_PRESSED_ENUM; i++) { m_keysPressed[i] = NULL; }
	for (int i = 0; i < SIZE_OF_MOUSE_PRESSED_ENUM; i++) { m_mousePressed[i] = NULL; }
}

Input::~Input()
{

}

void Input::Update()
{
	//loop through all the events in the event list
	//|| SDL_PollEvent(&m_MouseEvent) != NULL
	while (SDL_PollEvent(&m_KeyEvent) != NULL)
	{

		//first check for keydown
		if (m_KeyEvent.type == SDL_KEYDOWN) {
			//cache the code of key we pressed for easier debugging
			SDL_Keycode keyPressed = m_KeyEvent.key.keysym.sym;

			//update keys
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				m_keysPressed[KEY_ESCAPE] = true;
				break;
			case SDLK_a:
				m_keysPressed[KEY_A] = true;
				break;
			case SDLK_d:
				m_keysPressed[KEY_D] = true;
				break;
			case SDLK_SPACE:
				m_keysPressed[KEY_SPACE] = true;
				break;
			}
		}

		//second check for key up
		else if (m_KeyEvent.type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = m_KeyEvent.key.keysym.sym;

			//update keys
			switch (keyPressed)
			{
			case SDLK_a:
				m_keysPressed[KEY_A] = false;
				break;
			case SDLK_d:
				m_keysPressed[KEY_D] = false;
				break;
			case SDLK_SPACE:
				m_keysPressed[KEY_SPACE] = false;
				break;
			}
		}
	}
	//while (SDL_PollEvent(&m_MouseEvent) != NULL)
	//{
		//std::cout << "mouse test" << std::endl;
		/*switch (m_MouseEvent.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			std::cout << "test" << std::endl;
			break;
		}*/

		//third check for mouse down
		/*if (m_MouseEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			switch (m_MouseEvent.button.button)
			{
			case SDL_BUTTON_LEFT:
				std::cout << "Left mouse clicked" << std::endl;
				break;
			case SDL_BUTTON_RIGHT:
				std::cout << "Left mouse clicked" << std::endl;
				break;


			}





		}*/



		//fourth check for mouse up
	//}
}

bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keysPressed[key];
}

void Input::KeyIsNotPressed(KEYS_PRESSED_LIST &key)
{
	m_keysPressed[key] = false;
}

bool Input::MouseIsPressed(MOUSE_PRESSED_LIST mouse)
{
	//to do
	return false;
}

bool Input::MouseIsNotPressed(MOUSE_PRESSED_LIST& mouse)
{
	//to do
	return false;
}
