#pragma once
#include <string>
#include <vector>

class PlayState;
class GameObject;
class Texture;


class Map;
using namespace std;

class Room
{
public:

	Room();
	~Room();
	void loadTexture();
	void render();
	int getX();
	int getY();
	bool getUpDoor();
	bool getRightDoor();
	bool getLeftDoor();
	bool getDownDoor();
	bool getVisited();
	string getSpecial();
	Map* getMap() { return map; }
	void setX(int x);
	void setY(int y);
	void setUpDoor(bool upDoor);
	void setRightDoor(bool rightDoor);
	void setLeftDoor(bool leftDoor);
	void setDownDoor(bool downDoor);
	void setVisited(bool visited);
	void setSpecial(string special);
	void spawn();
	void update();

private:
	string filename;
	//PlayState* playState;
	Texture* texture;
	Map* map;
	int x;
	int y;
	bool upDoor;
	bool rightDoor;
	bool downDoor;
	bool leftDoor;
	bool visited;
	string special;//Boss, chest, or shop	
};

