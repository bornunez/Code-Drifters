#pragma once
#include "UpperGameState.h"

class Shop;

class ShopState: public UpperGameState
{
public:
	ShopState(GameState* upper);
	~ShopState();
};

