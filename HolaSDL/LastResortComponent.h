#pragma once
#include"PlayState.h"
#include"UpdateComponent.h"

class LastResortComponent : public UpdateComponent
{
public:
	void receiveMessage(Message* msg);
	LastResortComponent(MainCharacter* mc);
	~LastResortComponent();
	void update() {};
protected:
	MainCharacter* character = nullptr;
};

