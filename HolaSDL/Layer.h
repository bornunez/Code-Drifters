#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;
class Camera;

class Layer
{
protected:
	string layerID;
public:
	Layer(string name) : layerID(name) {};
	~Layer();
	virtual void update() = 0;
	virtual void render(Camera* camera) = 0;
	string getLayerID() { return layerID; }
};

