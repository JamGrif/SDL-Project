#pragma once
#include <SDL.h>
#include <iostream>
enum KEYS_PRESSED_LIST 
{
	KEY_ESCAPE, KEY_A, KEY_D, KEY_SPACE, SIZE_OF_KEYS_PRESSED_ENUM
};
enum MOUSE_PRESSED_LIST 
{
	MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE, SIZE_OF_MOUSE_PRESSED_ENUM
};
class Input
{
public:
	Input();
	~Input();

	void Update();
	bool KeyIsPressed(KEYS_PRESSED_LIST key);
	void KeyIsNotPressed(KEYS_PRESSED_LIST &key);
	void CheckForKeyPress();

	bool MouseIsPressed(MOUSE_PRESSED_LIST mouse);
	bool MouseIsNotPressed(MOUSE_PRESSED_LIST &mouse);
	
	
private:
	SDL_Event m_KeyEvent;
	SDL_Event m_MouseEvent;
	
	bool m_keysPressed[SIZE_OF_KEYS_PRESSED_ENUM];
	bool m_mousePressed[SIZE_OF_MOUSE_PRESSED_ENUM];
};

