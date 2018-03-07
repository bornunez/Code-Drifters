#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;
class Camera;

class Layer
{
private:

public:
	Layer();
	~Layer();
	virtual void update() = 0;
	virtual void render(Camera* camera) = 0;
};

