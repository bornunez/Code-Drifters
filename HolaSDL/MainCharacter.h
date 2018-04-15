#pragma once
#include "Animation.h"
#include <map>
#include "BulletManager.h"

#include "Hook.h"

class HookShotComponent;
class PlayState;
class MCAnimationComponent;
enum MCState { Idle, Run, Attack, Shot, Hooking, Hurt, Heal, DashEnd };

class MainCharacter : public GameObject
{
private:
	float HP;
	float velocity;
	float maxVelocity;
	float normalAttackDamage;
	float chargedAttackDamage;
	MCState mcState = MCState::Idle;
	int maxBullets;
	int currentBullets;
	int reloadTime;
	Vector2D gunPosition;//Posici�n de donde sale la bala
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
	float getNormalAttackDamage();//Devuelve el da�o que hace el ataque normal
	void setNormalAttackDamage(float dmg);//Cambia el da�o que hace el ataque normal
	float getChargedAttackDamage();//Devuelve el da�o que hace el ataque normal
	void setChargedAttackDamage(float dmg);//Cambia el da�o que hace el ataque normal
	float getAttackDamage(std::string attackType);//Seg�n el ataque que sea, devuelve su da�o
	void setMaxVelocity(float vel);
	float getVelocity();
	float getMaxVelocity();
	float getHP();
	Vector2D getGunPosition();
	void setGunPosition(Vector2D pos);
	void substractHP(int damage);
	void addHP(int life);
	int getReloadTime();
	void setReloadTime(int miliseconds);
	void setMCState(MCState state) { this->mcState = state; };
	MCState getMCState() { return mcState; };
	
	//HOOK
	Hook getHook() { return hook; }
	void shootHook(Vector2D originPos, Vector2D hookDir);
};


