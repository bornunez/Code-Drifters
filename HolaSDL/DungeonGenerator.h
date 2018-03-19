#pragma once
#include <vector>
#include "sdl_includes.h"
class Room;
class Game;
class PlayState;

using namespace std;
class DungeonGenerator
{
public:
	DungeonGenerator(int mapWidth, int mapHeight, int maxRooms);
	~DungeonGenerator();
	void CreateMap();

	Room* getRoom(int x, int y);
	Room* getFirstRoom();

private:
	void ClearMap();
	vector<Room*> FindDeadEnds();
	void CreateSpecialRooms();
	void AddFirstRoom();
	vector<string> CheckDirections(int x, int y);
	void GenerateDungeon();
	void CreateRoom(int x, int y);
	void FixDoors();
	void UnvisitedRoomToQueue(vector<string> posibleDirections_, string direction, int x, int y);
	void SetRoomDirections(vector<string> posibleDirections_, string direction, int x, int y);
	void SetEntryDoor(int x, int y, string direction);
	bool CellInsideBounds(int x, int y);
	void load();
	bool AvailableCell(int x, int y);

	int mapWidth_;
	int mapHeight_;
	int maxRooms_;
	int roomsLeft_;
	vector<Room*> visitedRooms_;
	vector<Room*> unvisitedRooms_;
	vector<vector<Room*>> Dungeon_;

};

