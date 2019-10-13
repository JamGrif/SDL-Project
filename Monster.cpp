#include "Monster.h"

Monster::Monster(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture)
	:Creature(renderer, xpos, ypos, useTransparency, DefaultPicture)
{
	std::cout << "Monster created!" << std::endl;


}
