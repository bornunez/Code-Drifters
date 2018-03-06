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

	Room(PlayState* playState);
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

	void setX(int x);
	void setY(int y);
	void setUpDoor(bool upDoor);
	void setRightDoor(bool rightDoor);
	void setLeftDoor(bool leftDoor);
	void setDownDoor(bool downDoor);
	void setVisited(bool visited);
	void setSpecial(string special);
	void addCharacter(GameObject* o);


private:
	string filename;
	PlayState* playState;
	Texture* texture;
	Map* map;
	vector<GameObject*> characters;//Todos los elementos que aparecen en pantalla
	int x;
	int y;
	bool upDoor;
	bool rightDoor;
	bool downDoor;
	bool leftDoor;
	bool visited;
	string special;//Boss, chest, or shop	
};

