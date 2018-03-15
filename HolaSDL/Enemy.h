#pragma once
#include "GameObject.h"

class MainCharacter;
class Game;
class PlayState;
class Spawner;
enum EnemyType;

class Enemy : public GameObject
{
protected:
//################## ATRIBUTOS COMUNES ####################
	int life;
	int meleeDmg; int rangedDmg;
	int minDrop; int maxDrop; //Drop de dinero
	GameObject* mainCharacter;
//#########################################################

	//Necesario para el ciclo de salas
	Spawner* spawner = nullptr;

	//Cosas que definen los hijos
	EnemyType type;

	//Metodos auxiliares
	void receiveDamage(int damage);
	void onDestroy();

	friend class EnemyManager;
	Enemy(MainCharacter* mc);
public:
	~Enemy();
	virtual void spawn(int x, int y, Spawner* spawner = nullptr);
	virtual void render();
	virtual void update();
	GameObject* getMC();
	EnemyType getType() { return type; }


};

