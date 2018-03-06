#pragma once
#include <string>
#include "Texture.h"
#include "GameObject.h"

class Game;
class Map;
using namespace std;

class Room
{
public:

	Room(Game* game);
	Room(Game* game, SDL_Rect rect);
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
	SDL_Rect rect;
	Game* game;
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

