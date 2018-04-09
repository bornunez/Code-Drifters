#pragma once
#include <vector>
using namespace std;

class Room;
class DungeonGenerator;

enum Direction{Up,Right,Down,Left};
struct DirPair { int x; int y; };

class LevelManager
{
private:

	//Singleton
	static LevelManager * instance;
	LevelManager();

	//Cosas de puertas
	vector<DirPair> directions;

	//Progreso del jugador
	int level;
	int baseRooms;
	int roomsPerLevel;
	//Posicion del jugador
	int roomX, roomY;
	Room* currentRoom;
	Room* firstRoom;
	DungeonGenerator* dungeon;

public:
	static LevelManager * getInstance();

	DungeonGenerator* getLevel() { return dungeon; }
	Room* getCurrentRoom() { return currentRoom; }
	Room* getFirstRoom() { return firstRoom; }
 
	Room* getRoom(int x, int y);
	Room* getRoom(Direction dir);

	void changeRoom(Room* room);
	void changeRoom(int x, int y);
	void changeRoom(Direction dir);
	void render();

	bool getDoor(Direction dir);

	//Metodos de control
	void init();
	void newMap();
	~LevelManager();
};