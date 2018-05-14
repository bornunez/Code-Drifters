#pragma once
#include "GameState.h"
#include "Texture.h"
#include "MenuButton.h"
#include "Font.h"
class Game;
class MainMenuState: public GameState
{
private:
	//MenuButton* start;
	MenuButton* exit;

	//Texture* playButtonTex;
	Texture* exitButtonTex;

	Font* font;
	Texture* openText;
	SDL_Rect textRect;

	Texture* background;
	SDL_Rect bckgrndRect;

	SDL_Rect pbPos;
	SDL_Rect ebPos;

	SDL_Color c;
	bool alfaUp = false;

public:
	MainMenuState();
	virtual ~MainMenuState();
	
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	virtual void render();
	static void playState(Game* game);
	static void exitGame(Game* game);
};

