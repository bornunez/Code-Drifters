#include "ShopState.h"
#include "Button.h"



ShopState::ShopState(GameState* upper): UpperGameState(upper)
{
	gameObjects.push_back(new Shop(this));
}


ShopState::~ShopState()
{
}

void ShopState::createButton(SkillTree* skill)
{
	gameObjects.push_back(new Button(skill));
}


