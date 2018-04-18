#pragma once
#include "UpdateComponent.h"
#include "GameObject.h"
class UpdateBoss : public UpdateComponent
{
public:
	UpdateBoss(GameObject* o);
	~UpdateBoss();
protected:
	virtual void update();
private:
	GameObject* boss;
};

