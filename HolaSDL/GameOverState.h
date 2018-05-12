#pragma once
#include "GameState.h"
#include "Texture.h"
#include "Font.h"
class Game;
class GameOverState: public GameState
{
private:

	Font* font;
	Font* font2;

	Texture* op1Tex;
	Texture* op2Tex;
	Texture* op3Tex;

	SDL_Rect op1Rect;
	SDL_Rect op2Rect; 
	SDL_Rect op3Rect;

	Texture* title2;
	Texture* title1;

	SDL_Rect title1Rect;
	SDL_Rect title2Rect;

	Texture* deathChar;
	SDL_Rect deathRect;

	SDL_Color white = { COLOR(0xF615E0ff)};
	SDL_Color blue = { COLOR(0x34D6F6ff) };

	SDL_Point mouse;
	bool alfaUp = false;
	bool flag = false;
	int selectedOp = 0;

public:
	GameOverState();
	~GameOverState();
	
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	virtual void render();
	void changeColors();
	static void playState(Game* game);
	static void exitGame(Game* game);
};

