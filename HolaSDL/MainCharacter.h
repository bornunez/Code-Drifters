#pragma once
#include "Animation.h"
#include <map>
#include "Hook.h"
#include "HookShotComponent.h"
class PlayState;
class MCAnimationComponent;
enum ActionState { Idle, Run, Attack, Shoot, Hooking, Hurt, Heal };
class MainCharacter : public GameObject
{
private:
	float HP;
	float velocity;
	float maxVelocity;
	float normalAttackDamage;
	float chargedAttackDamage;
	bool activeHook;
	bool firingGun;
	bool attacking;
	ActionState actionState = Idle;
	int maxBullets;
	int currentBullets;
	int reloadTime;
	Vector2D gunPosition;//Posición de donde sale la bala
	Hook hook;
	
	HookShotComponent* hookShot;


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
	float getNormalAttackDamage();//Devuelve el daño que hace el ataque normal
	void setNormalAttackDamage(float dmg);//Cambia el daño que hace el ataque normal
	float getChargedAttackDamage();//Devuelve el daño que hace el ataque normal
	void setChargedAttackDamage(float dmg);//Cambia el daño que hace el ataque normal
	float getAttackDamage(std::string attackType);//Según el ataque que sea, devuelve su daño
	void setMaxVelocity(float vel);
	float getVelocity();
	float getMaxVelocity();
	float getHP();
	Vector2D getGunPosition();
	void setGunPosition(Vector2D pos);
	void substractHP(int damage);
	int getReloadTime();
	void setReloadTime(int miliseconds);
	void setActionState(ActionState actionState) { this->actionState = actionState; };
	ActionState getActionState() { return actionState; };
	
	//HOOK
	void shootHook(Vector2D originPos, Vector2D hookDir);
};


