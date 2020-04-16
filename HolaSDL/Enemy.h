#pragma once
//#include "checkML.h"
#include "GameObject.h"
#include <string>
class Timer;
class MainCharacter;
class Game;
class PlayState;
class Spawner;
class EnemyHUDComponent;
enum EnemyType;
enum class EnemyState {Idle, Run, Hurt, Shoot, Charge, Death, Attack, Hooked};

//################## ATRIBUTOS COMUNES ####################
struct CommonBossAttributes {
	float life,maxLife;
	float speed;
	float meleeDmg; float rangedDmg;
	int minDrop; int maxDrop; //Drop de dinero
	int healDrop;
	bool stunned = false;
	bool hookable = true;
};
//#########################################################

class Enemy : public GameObject
{
protected:
	EnemyHUDComponent * hud;
	CommonBossAttributes Attributes;
	MainCharacter* mainCharacter;

	//Necesario para el ciclo de salas
	Spawner* spawner = nullptr;

	//Cosas que definen los hijos
	EnemyType type;

	//Metodos auxiliares
	


	friend class EnemyManager;
	Enemy(MainCharacter* mc);
	
public:
	virtual ~Enemy();
	virtual void spawn(int x, int y, Spawner* spawner = nullptr);
	virtual void render();
	virtual void update();
	void onDestroy();
	void death();
	void hookCombo();
	MainCharacter* getMC();
	EnemyType getType() { return type; }
	float getMeleeDmg() { return Attributes.meleeDmg; }
	float getRangedDmg() { return Attributes.rangedDmg; }
	float getLife() { return Attributes.life; }
	float getMaxLife() { return Attributes.maxLife; }
	void setLife(int life) { Attributes.life = life; };
	void setStun(bool set) { Attributes.stunned = set; }
	bool isStunned() { return Attributes.stunned; }
	bool isHooked() { return (this->enemyState==EnemyState::Hooked); }
	bool isHookable() { return Attributes.hookable; }

	//TELEMETRIA
	bool hooked = false;
	float hookComboTime = 0.5f;
	bool isComboHooked() { return hooked; };
	Timer* timer;


	EnemyState enemyState;		//PROTECTED
	EnemyState getEnemyState() { return this->enemyState; }
	double baseSpeed;
};

