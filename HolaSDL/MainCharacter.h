#pragma once
//#include "checkML.h"
#include "Animation.h"
#include <map>
#include "BulletManager.h"

#include "Hook.h"

class HookShotComponent;
class PlayState;
class MCAnimationComponent;

enum class MCState { Idle, Run, Attack, ChargingAttack, ChargedAttack, Shot, HookShot, Dash, Hurt, Heal, DashEnd, Death , Ultimate};
enum class MCAttackType{NORMAL,CHARGED,ULTIMATE,SHOT};
class MainCharacter : public GameObject
{
private:
	string name = "Haro";

	float HP, maxHP;
	float gunStunTime = 2.5; //default stun time
	float velocity;
	float maxVelocity;
	float normalAttackDamage, chargedAttackDamage, ultimateAttackDamage, shotAttackDamage;
	MCState mcState = MCState::Idle;

	bool charging = false;//Booleano si determina si se está pulsando el botón para cargar el ataque

	int maxBullets;
	float currentBullets;
	float reloadTime;

	int money = 0;
	bool lifeStealEnabled = false;
	float lifeStealPercentual = 10.0; //percentage of the damage done that is healed

	float ultiCharge = 50;//[0,100]
	float UltiBonusCD = 1; //[ultiCharge / ultiBonus], which leads to bonus in range (0, 1]

	Vector2D gunPosition;//Posici�n de donde sale la bala
	Hook* hook;
	
	HookShotComponent* hookShot;


public:

	MainCharacter(Texture* tex, int x, int y, int w, int h);

	virtual ~MainCharacter();
	
	//Animations
	void loadAnimations();
	

	//Getters & Setters
	void setNormalAttackDamage(float dmg);//Cambia el da�o que hace el ataque normal
	void setChargedAttackDamage(float dmg);//Cambia el da�o que hace el ataque normal
	void setUltimateAttackDamage(float dmg);
	void setMaxVelocity(float vel);
	void setGunPosition(Vector2D pos);
	void setMCState(MCState state) { this->mcState = state; };

	void setCurrentBullets(float current);
	void setReloadTime(float newReloadTime);
	void setMaxBullets(int bullets);

	float getCurrentBullets();
	int getMaxBullets();
	float getReloadTime();

	float getAttackDamage(MCAttackType attackType);//Seg�n el ataque que sea, devuelve su da�o
	float getVelocity();
	float getMaxVelocity();
	float getActualHP();
	float getMaxHP();

	MCAttackType getCurrentAttackType();//Devuelve el tipo de ataque según el estado actual

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
	bool getCharging() { return charging; };
	void setCharging(bool b) { charging = b; };

	float getUltiDmg() { return ultimateAttackDamage; };
	void setUltiDmg(float newUltDmg) { ultimateAttackDamage = newUltDmg; };
	float getUltiBonusCD() { return UltiBonusCD; };
	///send a percentual cd reduction
	void setUltiBonusCD(float cdReduction) { UltiBonusCD -= (cdReduction / 100); if (UltiBonusCD <= 0) UltiBonusCD = 0.01; };
	
	//HOOK
	Hook* getHook() { return hook; }
	void shootHook(Vector2D originPos, Vector2D hookDir);

	//ULTIMATE CHARGE
	float getUltiCharge() { return ultiCharge; }
	void setUltiCharge(float num) { 
		ultiCharge = num; 
		ultiCharge = min(100.0f, ultiCharge);
		ultiCharge = max(ultiCharge, 0.0f);
	}
	void setStunTime(float newTotalTime) { gunStunTime = newTotalTime; };
	float getStunTime() { return gunStunTime; };
};


