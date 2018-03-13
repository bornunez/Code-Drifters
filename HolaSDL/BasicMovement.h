#pragma once
#include "UpdateComponent.h"
#include <vector>

using namespace std;

class TileLayer;
class BasicMovement : public UpdateComponent
{
private:
	vector<string> collisionsLayer;
public:
	BasicMovement(GameObject* o);
	BasicMovement(GameObject * o,string layer);
	BasicMovement(GameObject * o, vector<string> collisionsL);
	virtual ~BasicMovement();
	void update();
	void recieveMessage(std::string msg) {};
};

