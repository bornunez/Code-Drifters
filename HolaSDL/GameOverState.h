#pragma once
//#include "checkML.h"
#include "GameState.h"
#include "Texture.h"
#include "Font.h"
class Game;
class GameOverState: public GameState
{
private:

	Font* font;
	Font* font2;

	string op1;
	string op2;
	string op3;

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

	SDL_Color white;
	SDL_Color blue;

	SDL_Point mouse;
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

