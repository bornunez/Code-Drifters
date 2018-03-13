#pragma once
#include "UpdateComponent.h"
class UpdateBoss:public UpdateComponent
{
public:
	void update();
	void recieveMessage(std::string msg) {};
	UpdateBoss(GameObject* o);
	~UpdateBoss();
};

