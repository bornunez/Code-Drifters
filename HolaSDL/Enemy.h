#pragma once
#include "GameObject.h"
#include <string>
class MainCharacter;
class Game;
class PlayState;
class Spawner;
enum EnemyType;
enum class EnemyState {Idle, Run, Hurt, Shoot, Charge, Death, Attack};

//################## ATRIBUTOS COMUNES ####################
struct CommonAttributes {
	float life; float defense;
	float speed;
	float meleeDmg; float rangedDmg;
	int minDrop; int maxDrop; //Drop de dinero
	bool stunned = false;
};
//#########################################################

class Enemy : public GameObject
{
protected:

	CommonAttributes Attributes;
	GameObject* mainCharacter;

	//Necesario para el ciclo de salas
	Spawner* spawner = nullptr;

	//Cosas que definen los hijos
	EnemyType type;

	//Metodos auxiliares
	


	friend class EnemyManager;
	Enemy(MainCharacter* mc);
	
public:
	/*void receiveDamage(int damage);*/

	
	~Enemy();
	virtual void spawn(int x, int y, Spawner* spawner = nullptr);
	virtual void render();
	virtual void update();
	void onDestroy();
	void death();
	GameObject* getMC();
	EnemyType getType() { return type; }
	void knockBack();
	float getDefense() { return Attributes.defense; };
	float getLife() { return Attributes.life; }
	void setLife(int life) { Attributes.life = life; };
	void setStun(bool set) { Attributes.stunned = set; }
	bool isStunned() { return Attributes.stunned; }
	EnemyState enemyState;		//PROTECTED
	EnemyState getEnemyState() { return this->enemyState; }
};

