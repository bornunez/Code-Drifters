#pragma once
#include "InputComponent.h"
class ShopInput :
	public InputComponent
{
public:
	ShopInput(GameObject* o);
	~ShopInput();

	void handleEvents(SDL_Event & e);
};

