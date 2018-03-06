#pragma once
#include "PlayStateObject.h"

class MainCharacter;
class Game;
class PlayState;

class Enemy : public PlayStateObject
{
private:
	int life;
	int contactDamage;
	GameObject* mainCharacter;
	PlayState* playState;

	void receiveDamage(int damage);
	void onDestroy();

public:
	Enemy(PlayState* playState, Game* game, MainCharacter* mc, Transform t);
	Enemy(PlayState* playState, Game* game, MainCharacter* mc, int x, int y, int w, int h);
	~Enemy();
	void render();

	GameObject* getMC();


};

