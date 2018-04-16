#pragma once
#include "UpdateComponent.h"

class MainCharacter;

class ReloadComponent :
	public UpdateComponent
{
private:
	MainCharacter * mc;
	bool active = true;
public:
	ReloadComponent(MainCharacter* mc);
	virtual ~ReloadComponent();
	virtual void update();

	void stop() { active = false; }
	void resume() { active = true; }
	void restart();
};

