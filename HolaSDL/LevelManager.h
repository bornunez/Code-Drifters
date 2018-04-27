#pragma once
#include <vector>
using namespace std;

class Room;
class DungeonGenerator;

enum Direction{Up,Right,Down,Left, None};
struct DirPair { int x; int y; };
enum LevelType{ City, Red};

class LevelManager
{
private:
	//Singleton
	static LevelManager * instance;
	LevelManager();

	void onRoomChange(Room * room, Direction dir);

	//Cosas de puertas
	vector<DirPair> directions;

	//Progreso del jugador
	int level;
	int baseRooms;
	int roomsPerLevel;
	vector<string> levelTypePath { "City_Levels\\" , "Red_Levels\\" };

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
	void enterMap();
 
	Room* getRoom(int x, int y);
	Room* getRoom(Direction dir);

	void changeRoom(Room* room);
	void changeRoom(int x, int y);
	void changeRoom(Direction dir);
	Room* getBossRoom();

	void render();

	bool getDoor(Direction dir);

	string getActiveLevelPath() { return levelTypePath[City]; }

	//Metodos de control
	void init();
	void newMap();
	~LevelManager();
};