#pragma once
#include "GameObject.h"
class MasterBoss:public GameObject
{
public:
	MasterBoss();
	~MasterBoss();

protected:
	int vida;
	float da�o;
	virtual void update() = 0;
	virtual void render() = 0;
};

