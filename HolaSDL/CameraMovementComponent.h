#pragma once
#include "UpdateComponent.h"
class CameraMovementComponent : public UpdateComponent
{
private:
	GameObject * mainCharacter;
	Vector2D lastPos;
	int offset;
public:
	void update();
	CameraMovementComponent(GameObject* camera, GameObject* mainCharacter);
	~CameraMovementComponent();
	void receiveMessage(std::string msg) {};
};

