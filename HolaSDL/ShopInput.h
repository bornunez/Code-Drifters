#pragma once
//#include "checkML.h"
#include "InputComponent.h"
class ShopInput :
	public InputComponent
{
public:
	ShopInput(GameObject* o);
	virtual ~ShopInput();

	void handleEvents(SDL_Event & e);
};

