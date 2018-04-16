#pragma once
#include "Animation.h"
#include <map>
#include "BulletManager.h"

#include "Hook.h"

class HookShotComponent;
class PlayState;
class MCAnimationComponent;

enum class MCState { Idle, Run, Attack, Shot, HookShot, Dash, Hurt, Heal, DashEnd, Death };

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
	float currentBullets;
	float reloadTime;

	Vector2D gunPosition;//Posici�n de donde sale la bala
	Hook hook;
	
	HookShotComponent* hookShot;


public:

	MainCharacter(Texture* tex, int x, int y, int w, int h);

	~MainCharacter();
	
	//Animations
	void loadAnimations();
	

	//Getters & Setters
	void setNormalAttackDamage(float dmg);//Cambia el da�o que hace el ataque normal
	void setChargedAttackDamage(float dmg);//Cambia el da�o que hace el ataque normal
	void setMaxVelocity(float vel);
	void setGunPosition(Vector2D pos);
	void setMCState(MCState state) { this->mcState = state; };

	void setCurrentBullets(float current);
	void setReloadTime(float newReloadTime);
	void setMaxBullets(int bullets);

	float getCurrentBullets();
	int getMaxBullets();
	float getReloadTime();

	float getNormalAttackDamage();//Devuelve el da�o que hace el ataque normal
	float getChargedAttackDamage();//Devuelve el da�o que hace el ataque normal
	float getAttackDamage(std::string attackType);//Seg�n el ataque que sea, devuelve su da�o
	float getVelocity();
	float getMaxVelocity();
	float getHP();
	Vector2D getGunPosition();
	void substractHP(int damage);
	void addHP(int life);
	MCState getMCState() { return mcState; };
	
	//HOOK
	Hook getHook() { return hook; }
	void shootHook(Vector2D originPos, Vector2D hookDir);
};


