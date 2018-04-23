#pragma once
#include <string>
#include <vector>

class PlayState;
class GameObject;
class Texture;


class Map;
using namespace std;
enum Direction;
enum RoomType {First, Normal, Boss, Shop, Chest};

class Room
{
public:

	Room();
	~Room();
	void load();
	void render();
	void setAllDoors(bool set);

	int getX();
	int getY();
	bool getDoor(Direction door);
	bool getVisited();
	RoomType getType() { return type; }
	void setType(RoomType type) { this->type = type; }
	Map* getMap() { return map; }
	void setX(int x);
	void setY(int y);
	void setDoor(Direction door, bool set);
	void setVisited(bool visited);
	bool isVoid() { return voidRoom; }
	bool isExplored() { return explored; }
	void setExplored(bool explored) { this->explored = explored; }
	void spawn();
	void update();

private:
	string filename;
	string getPath();
	Map* map;
	int x;
	int y;
	vector<bool> doors;

	bool visited; //Indica si el generador la ha visitado
	bool voidRoom; //Indica que la sala se ha creado
	bool explored; //Indica si el jugador ha visitado la sala
	RoomType type;
};

