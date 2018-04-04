#pragma once
#include "UpdateComponent.h"
#include "Vector2D.h"
#include "Timer.h"
class MainCharacter;
class Hook;
class HookShotComponent :
	public UpdateComponent
{
private:
	float hookSpeed;
	Hook * hook;
	MainCharacter* mc;
public:
	void update();
	void receiveMessage(std::string msg) {};
	void shoot(Vector2D originPos, Vector2D hookDir);
	void extend();
	void contract();
	void stop();
	HookShotComponent(MainCharacter* mc, Hook* h, float hookSpeed);
	virtual ~HookShotComponent();
};

