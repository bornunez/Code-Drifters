#pragma once
#include "UpdateComponent.h"
#include <string>
#include "CollisionHandler.h"
#include "PlayState.h"
#include "MainCharacter.h"

using namespace std;

class TextTrigger :
	public UpdateComponent
{
private:
	string textPath;
public:
	TextTrigger(GameObject * o,string path);
	virtual ~TextTrigger();
	void update();
};

