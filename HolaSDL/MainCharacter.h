#pragma once
#include "PlayStateObject.h"

class PlayState;


class MainCharacter : public PlayStateObject
{
private:
	int currentRoomX;
	int currentRoomY;
	float HP;
	float velocity;
	float maxVelocity;
	float meleeDamage;
	bool activeHook;
	bool firingGun;
	bool attacking;
	int maxBullets;
	int currentBullets;

public:

	MainCharacter(PlayState* playState, Game* game, Texture* tex, int x, int y, int w, int h);

	~MainCharacter();
	void render();

	//Getters & Setters
	void addCurrentBullets(int num);
	int getCurrentBullets();
	void setMaxBullets(int bullets);
	float getMeleeDamage();
	void setMeleeDamage(float dmg);
	void setMaxVelocity(float vel);
	float getVelocity();
	float getMaxVelocity();
	float getHP();
	void substractHP(int damage);
	int getCurrentRoomX();
	int getCurrentRoomY();
	void changeCurrentRoom(int x, int y);
};

