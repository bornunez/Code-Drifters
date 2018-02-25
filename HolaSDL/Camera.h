#pragma once
#include <vector>
#include "DungeonGenerator.h"
#include "GameObject.h"
#include "Transform.h"
class Camera :	public GameObject
{
private:
	int currentRoomX_;
	int currentRoomY_;
	
	vector<vector<Room*>> Dungeon_;
public:
	Room * getCurrentRoom(int posX, int posY);
	void setCurrentRoom(int posX, int posY);
	Camera();	
	~Camera();
	virtual void update();
	virtual void render();
};

