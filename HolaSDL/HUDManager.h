#pragma once
//#include "checkML.h"
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
	std::vector<HUDObject*> fullBullets;
	std::vector<HUDObject*> bulletBack;

	HUDObject* lifeSkeleton;
	HUDObject* lifeBar;
	HUDObject* lifeBack;

	HUDObject* ultSkeleton;
	HUDObject* ultBar;
	HUDObject* fullUlt;
	HUDObject* ultBack;

	Font* moneyFont = nullptr;
	Texture* moneyTex = nullptr;
	SDL_Rect moneyDestRect;
	SDL_Color moneyColor;

	int gameScale = 0;
	float lifeUnit;
public:
	void init(MainCharacter* MC);
	HUDManager();
	~HUDManager();
	static HUDManager* getInstance();
	static void ResetInstance();

	void update();
	void render();
	void setNewHP(int newL);
	void addBullet();
	void changeLife(int l);
	void ActualizeMoney();
};

