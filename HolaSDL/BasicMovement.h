#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include <vector>

using namespace std;

class TileLayer;
class BasicMovement : public UpdateComponent
{
public:
	BasicMovement(GameObject* o);
	virtual ~BasicMovement();
	void update();
	void receiveMessage(std::string msg) {};
};

