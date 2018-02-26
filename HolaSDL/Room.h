#pragma once
#include <string>
#include "Texture.h"
#include "GameObject.h"
#include "Game.h"

using namespace std;

class Room
{
public:

	Room();
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

private:
	string filename_;
	SDL_Rect rect_;
	Game* game_;
	Texture* texture;
	vector<GameObject*> characters_;//Todos los elementos que aparecen en pantalla
	int x_;
	int y_;
	bool upDoor_;
	bool rightDoor_;
	bool downDoor_;
	bool leftDoor_;
	bool visited_;
	string special_;//Boss, chest, or shop	
};

