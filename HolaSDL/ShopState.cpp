#include "ShopState.h"
#include "Button.h"



ShopState::ShopState(GameState* upper): UpperGameState(upper)
{
	shopBox = new ShopBox();
	gameObjects.push_back(new Shop(this));
	gameObjects.push_back(shopBox);
}


ShopState::~ShopState()
{
}

void ShopState::createButton(SkillTree* skill)
{
	gameObjects.push_back(new Button(skill));
}


