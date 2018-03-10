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
	int reloadTime;
	Vector2D gunPosition;//Posici�n de donde sale la bala

public:

	MainCharacter(PlayState* playState, Game* game, Texture* tex, int x, int y, int w, int h);

	~MainCharacter();
	//void render();

	//Getters & Setters
	void setCurrentBullets(int num);
	int getCurrentBullets();
	void setMaxBullets(int bullets);
	int getMaxBullets();
	float getMeleeDamage();
	void setMeleeDamage(float dmg);
	void setMaxVelocity(float vel);
	float getVelocity();
	float getMaxVelocity();
	float getHP();
	Vector2D getGunPosition();
	void setGunPosition(Vector2D pos);
	void substractHP(int damage);
	int getCurrentRoomX();
	int getCurrentRoomY();
	void changeCurrentRoom(int x, int y);
	int getReloadTime();
	void setReloadTime(int miliseconds);
};


