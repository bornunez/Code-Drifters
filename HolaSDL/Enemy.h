#pragma once
#include "PlayStateObject.h"

class MainCharacter;
class Game;
class PlayState;
enum EnemyType;

class Enemy : public PlayStateObject
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
	Enemy(PlayState* playState, MainCharacter* mc);
public:
	~Enemy();
	virtual void spawn(int x, int y);
	virtual void render();
	virtual void update();
	GameObject* getMC();
	EnemyType getType() { return type; }


};

