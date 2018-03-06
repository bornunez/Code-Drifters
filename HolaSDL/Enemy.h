#pragma once
#include "GameObject.h"

class MainCharacter;
class Game;

class Enemy : public GameObject
{

private:
	int life;
	int contactDamage;
	GameObject* mainCharacter;

	void receiveDamage(int damage);
	void onDestroy();

public:
	Enemy(Game* game, MainCharacter* mc, Transform t);
	Enemy(Game* game, MainCharacter* mc, int x, int y, int w, int h);
	~Enemy();
	void render();

	GameObject* getMC();


};

