#pragma once
//#include "checkML.h"
#include "GameObject.h"
#include "SkillTree.h"

using namespace std;

class Button: public GameObject
{
private:
	SDL_Rect rect;
	SDL_Point mouse;
	SkillTree* skill_;

	bool cursorOn;

public:
	Button(SkillTree* skill);
	virtual ~Button();
	void handleEvents(SDL_Event& e);
	void update();
};

