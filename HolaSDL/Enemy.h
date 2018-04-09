#pragma once
#include "GameObject.h"
#include <string>
class MainCharacter;
class Game;
class PlayState;
class Spawner;
enum EnemyType;
enum class EnemyState {Idle,Run, Hurt, Shoot, Charge, Death};
class Enemy : public GameObject
{
protected:
//################## ATRIBUTOS COMUNES ####################
	float life; float defense;
	float meleeDmg; float rangedDmg;
	int minDrop; int maxDrop; //Drop de dinero
	GameObject* mainCharacter;
	bool stunned = false;
//#########################################################

	//Necesario para el ciclo de salas
	Spawner* spawner = nullptr;

	//Cosas que definen los hijos
	EnemyType type;

	//Metodos auxiliares
	

	friend class EnemyManager;
	Enemy(MainCharacter* mc);
	
public:
	/*void receiveDamage(int damage);*/
	EnemyState enemyState;
	
	~Enemy();
	virtual void spawn(int x, int y, Spawner* spawner = nullptr);
	virtual void render();
	virtual void update();
	void onDestroy();
	GameObject* getMC();
	EnemyType getType() { return type; }
	void knockBack();
	float getDefense() { return defense; };
	float getLife() { return life; }
	void setLife(int life) { this->life = life; };
	void setStun(bool set) { stunned = set; }
	bool isStunned() { return stunned; }

};

