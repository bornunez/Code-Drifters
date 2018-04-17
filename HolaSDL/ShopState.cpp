#include "ShopState.h"
#include "Shop.h"



ShopState::ShopState(GameState* upper): UpperGameState(upper)
{
	gameObjects.push_back(new Shop());
}


ShopState::~ShopState()
{
}
