#pragma once
#include "GameObject.h"

class MainCharacter;
class Game;
class PlayState;
enum EnemyType;

class Enemy : public GameObject
{
protected:
//################## ATRIBUTOS COMUNES ####################
	int life;
	int meleeDmg; int rangedDmg;
	int speed; //Velocidad de movimiento
	int minDrop; int maxDrop; //Drop de dinero
	GameObject* mainCharacter;

//#########################################################

	//Cosas que definen los hijos
	EnemyType type;

	//Metodos auxiliares
	void receiveDamage(int damage);
	void onDestroy();

	friend class EnemyManager;
	Enemy(MainCharacter* mc);
public:
	~Enemy();
	virtual void spawn(int x, int y);
	virtual void render();
	virtual void update();
	GameObject* getMC();
	EnemyType getType() { return type; }


};

