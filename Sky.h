#pragma once
#include "Entity.h"
class Sky :
	public Entity
{
public:
	Sky(SDL_Renderer* renderer, int xpos, int ypos, bool useTransparency, std::string DefaultPicture = "");



};

