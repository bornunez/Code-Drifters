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
	std::map<const char*, Animation*> animations;
	MCAnimationComponent* animComp;//Se necesita para poder obtener un puntero a la animación actual
	Animation* runLeft;
	Animation* runRight;
	Animation* runTop;
	Animation* runBot;
	Animation* idleLeft;
	Animation* idleRight;
	Animation* idleTop;
	Animation* idleBot;
	Animation* attackLeft1;
	Animation* attackLeft2;
	Animation* attackLeft3;
	Animation* attackRight1;
	Animation* attackRight2;
	Animation* attackRight3;
	Animation* attackTopLeft1;
	Animation* attackTopLeft2;
	Animation* attackTopLeft3;
	Animation* attackTopRight1;
	Animation* attackTopRight2;
	Animation* attackTopRight3;
	


public:

	MainCharacter(Texture* tex, int x, int y, int w, int h);

	~MainCharacter();
	
	//Animations
	//void createRunAnimations();
	//void createIdleAnimation();
	//void createLeftAttackAnimation();
	//void createRightAttackAnimation();
	void loadAnimations();
	Animation* getCurrentAnimation();

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


