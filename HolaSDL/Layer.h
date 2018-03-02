#pragma once
#include <vector>
#include "GameObject.h"

using namespace std;
class Layer
{
private:
	vector<vector<GameObject*>> tiles;
public:
	Layer();
	~Layer();
};

