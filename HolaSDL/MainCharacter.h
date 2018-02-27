#pragma once
#include "GameObject.h"

class MainCharacter :public GameObject
{
	
public:
	MainCharacter(Game* game);
	~MainCharacter();
	void render();
};

