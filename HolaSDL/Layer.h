#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;
class Layer
{
public:
	Layer();
	~Layer();
	virtual void update() = 0;
	virtual void render() = 0;
};

