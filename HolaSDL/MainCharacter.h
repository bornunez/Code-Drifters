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
	string name = "Haro";

	float HP, maxHP;
	float velocity;
	float maxVelocity;
	float normalAttackDamage;
	float chargedAttackDamage;
	MCState mcState = MCState::Idle;

	int maxBullets;
	float currentBullets;
	float reloadTime;

	int money = 1000;
	bool lifeStealEnabled = false;
	float lifeStealPercentual = 10.0; //percentage of the damage done that is healed

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
	float getActualHP();
	float getMaxHP();
	int getMoney() { return money; };
	void changeMoney(int mon);
	Vector2D getGunPosition();
	void substractHP(int damage);
	void addHP(int life);
	MCState getMCState() { return mcState; };
	//different methods to use from the shop
	void addMaxHP(float life);
	void addPercentualDamage(float newDamage);
	void setLifeStealEnable(bool enable) { lifeStealEnabled = enable; };
	bool isLifeStealEnable() { return lifeStealEnabled; };
	float getLifeSteal() { return lifeStealPercentual; };
	void setLifeSteal(float multiplicator) { lifeStealPercentual *= multiplicator; };
	
	//HOOK
	Hook getHook() { return hook; }
	void shootHook(Vector2D originPos, Vector2D hookDir);
};


