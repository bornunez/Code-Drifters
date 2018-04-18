#pragma once
#include"MainCharacter.h"
#include"HUDObject.h"
class HUDManager
{
private:
	static HUDManager* instance;
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

	int gameScale = 0;
public:
	void init(MainCharacter* MC);
	HUDManager();
	~HUDManager();
	static HUDManager* getInstance();

	void update();
	void render();
	void setNewHP(int newL);
	void addBullet();
	void changeLife(int l);
};

