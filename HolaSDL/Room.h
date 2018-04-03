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
	void load();
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
	bool isVoid() { return voidRoom; }
	bool isExplored() { return explored; }
	void setExplored(bool explored) { this->explored = explored; }
	void spawn();
	void update();

private:
	string filename;
	Map* map;
	int x;
	int y;
	bool upDoor;
	bool rightDoor;
	bool downDoor;
	bool leftDoor;
	bool visited; //Indica si el generador la ha visitado
	bool voidRoom; //Indica que la sala se ha creado
	bool explored; //Indica si el jugador ha visitado la sala
	string special;//Boss, chest, or shop
};

