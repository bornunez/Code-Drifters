#pragma once

class MainCharacter;
class MapManager;
class PlayState;
class EnemyManager;
class BulletsManager;
class ResourceManager;
class Camera;
class Room;


class GameManager
{
private:
	static GameManager* instance;
	GameManager();
	
	//Distintos Managers
	MapManager * mapManager;
	EnemyManager* enemyManager;
	ResourceManager* resourceManager;
	BulletsManager * bulletsManager;

	//Variables de acceso rápido: OJO CUIDADO NO ABUSAR, pueden ser nullptr
	PlayState* playState;
	MainCharacter* mainCharacter;

public:
	~GameManager();
	static GameManager* getInstance();

	//Gets de los managers
	BulletsManager* getBulletsManager() { return bulletsManager; }
	EnemyManager* getEnemyManager() { return enemyManager; }
	ResourceManager* getResourceManager() { return resourceManager; }
	MapManager* getMapManager() { return mapManager; }

	//Gets y sets peligrosos
	MainCharacter* getMainCharacter() { return mainCharacter; }
	PlayState* getPlayState() { return playState; }
	void setMainCharacter(MainCharacter* mainCharacter) { this->mainCharacter = mainCharacter; }
	void setPlayState(PlayState* playState) { this->playState = playState; }
	Camera* getCamera();
	Room* getCurrentRoom();
	//Cosas del GameManager
	void init();
};


