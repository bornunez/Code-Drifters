#pragma once
//#include "checkML.h"
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
	virtual ~CameraMovementComponent();
	void receiveMessage(std::string msg) {};
};

