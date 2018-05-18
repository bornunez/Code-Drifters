#pragma once
//#include "checkML.h"
#include "UpperGameState.h"
#include "Shop.h"
#include "ShopBox.h"

class ShopState: public UpperGameState
{
private:
	ShopBox* shopBox;
public:
	ShopState(GameState* upper);
	virtual ~ShopState();

	void createButton(SkillTree* skill);
	void updateBox(string description, int price) { shopBox->actualiza(description, price); };
	void activeBox(bool active) { shopBox->setActive(active); };
	void handleEvent(SDL_Event& e);
};

