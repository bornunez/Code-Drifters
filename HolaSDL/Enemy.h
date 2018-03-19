#pragma once
#include "GameObject.h"
#include <string>
class MainCharacter;
class Game;
class PlayState;
class Spawner;
enum EnemyType;

class Enemy : public GameObject
{
protected:
//################## ATRIBUTOS COMUNES ####################
	int life; int defense;
	int meleeDmg; int rangedDmg;
	int minDrop; int maxDrop; //Drop de dinero
	GameObject* mainCharacter;
//#########################################################

	//Necesario para el ciclo de salas
	Spawner* spawner = nullptr;

	//Cosas que definen los hijos
	EnemyType type;

	//Metodos auxiliares
	
	void onDestroy();

	friend class EnemyManager;
	Enemy(MainCharacter* mc);
	
public:
	/*void receiveDamage(int damage);*/
	void receiveDamage(std::string attackType);
	~Enemy();
	virtual void spawn(int x, int y, Spawner* spawner = nullptr);
	virtual void render();
	virtual void update();
	GameObject* getMC();
	EnemyType getType() { return type; }


};

