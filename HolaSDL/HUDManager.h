#pragma once
#include"MainCharacter.h"
#include"HUDObject.h"
class HUDManager
{
private:
	//pointer to the character to get life, bullets, etc...
	MainCharacter* character = nullptr;

	std::vector<HUDObject*> bulletSkeleton;
	std::vector<HUDObject*> bullets_;
	std::vector<HUDObject*> bulletBack;

	HUDObject* lifeSkeleton;
	HUDObject* lifeBar;
	HUDObject* lifeBack;

	HUDObject* ultSkeleton;
	HUDObject* ultBar;
	HUDObject* ultBack;
public:
	HUDManager(MainCharacter* MC);
	~HUDManager();

	void update();
	void render();
	void setNewHP(float newL);
	void addBullet();
};

