#pragma once
#include "Animation.h"
#include <map>
#include "BulletManager.h"

#include "Hook.h"

class HookShotComponent;
class PlayState;
class MCAnimationComponent;
enum class MCState { Idle, Run, Attack, Shoot, Hooking, Hurt, Heal };

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
	void setMCState(MCState state) { this->mcState = state; };
	MCState getMCState() { return mcState; };
	
	//HOOK
	Hook getHook() { return hook; }
	void shootHook(Vector2D originPos, Vector2D hookDir);
};


