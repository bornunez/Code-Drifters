#pragma once
#include "GameState.h"
#include "sdl_includes.h"

class Camera;
class Game;
class MainCharacter;
class DungeonGenerator;

class PlayState : public GameState
{
private:
	Camera * camera;
	MainCharacter* mainCharacter;
	DungeonGenerator* dungeonGenerator;

	void loadState();
public:
	PlayState(Game* g);
	~PlayState();
	MainCharacter* getMainCharacter() { return mainCharacter; }
	virtual void render();
	virtual void handleEvent(SDL_Event& e);
	virtual void update();

	DungeonGenerator* getDungeonGenerator() { return this->dungeonGenerator; }
};

