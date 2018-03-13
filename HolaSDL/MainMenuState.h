#pragma once
#include "GameState.h"
#include "Texture.h"
#include "MenuButton.h"
class Game;
class MainMenuState: public GameState
{
private:
	MenuButton* start;
	MenuButton* exit;

	Texture* playButtonTex;
	Texture* exitButtonTex;

	SDL_Rect pbPos;
	SDL_Rect ebPos;

public:
	MainMenuState();
	~MainMenuState();
	
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	virtual void render();
	static void playState(Game* game);
	static void exitGame(Game* game);
};

