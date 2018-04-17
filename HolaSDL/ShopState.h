#pragma once
#include "UpperGameState.h"
#include "Shop.h"

class ShopState: public UpperGameState
{
private:

public:
	ShopState(GameState* upper);
	virtual ~ShopState();

	void createButton(SkillTree* skill);
};

