#pragma once
#include "GameObject.h"

class Enemy :public GameObject
{

public:
	Enemy();
	~Enemy();
private:
	int life;
	int contactDamage;
	

	void receiveDamage(int damage);
	void onDestroy();

};

