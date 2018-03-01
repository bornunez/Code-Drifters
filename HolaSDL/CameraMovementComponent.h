#pragma once
#include "UpdateComponent.h"
class CameraMovementComponent :
	public UpdateComponent
{
private:
	GameObject * mainCharacter;
public:
	void update();
	CameraMovementComponent(GameObject* camera, GameObject* mainCharacter);
	~CameraMovementComponent();
	void recieveMessage(std::string msg) {};
};

