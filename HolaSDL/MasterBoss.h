#pragma once
#include "GameObject.h"
class MasterBoss:public GameObject
{
public:
	MasterBoss();
	~MasterBoss();

protected:
	int vida;
	float daño;
};

