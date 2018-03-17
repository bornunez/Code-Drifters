#pragma once
#include "Animation.h"
#include <map>
class PlayState;
class MCAnimationComponent;
enum ActionState { Idle, Run, Attack, Shoot, Hook, Hurt, Heal };
class MainCharacter : public GameObject
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
	ActionState actionState = Idle;
	int maxBullets;
	int currentBullets;
	int reloadTime;
	Vector2D gunPosition;//Posición de donde sale la bala
	
	
	


public:

	MainCharacter(Texture* tex, int x, int y, int w, int h);

	~MainCharacter();
	
	//Animations
	void loadAnimations();
	

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
	void setActionState(ActionState actionState) { this->actionState = actionState; };
	ActionState getActionState() { return actionState; };
};


