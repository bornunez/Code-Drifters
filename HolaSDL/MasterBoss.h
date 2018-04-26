#pragma once
#include "GameObject.h"
//################## ATRIBUTOS COMUNES ####################
struct CommonAttributes {
	float life; float defense;
	float speed;
	float meleeDmg; float rangedDmg;
	int minDrop; int maxDrop; //Drop de dinero
	bool stunned = false;
};
class MasterBoss:public GameObject
{
public:
	MasterBoss();
	~MasterBoss();
	float getDefense() { return Attributes.defense; };
	float getLife() { return Attributes.life; }
	void setLife(int life) { Attributes.life = life; };
	void setStun(bool set) { Attributes.stunned = set; }
	bool isStunned() { return Attributes.stunned; }
	virtual void death() = 0;
	virtual void changeColor(int r, int g, int b) = 0;
protected:
	CommonAttributes Attributes;
};

