#pragma once
//#include "checkML.h"
#include "GameState.h"
#include "Texture.h"
#include "MenuButton.h"
#include "Font.h"
class Game;
class MainMenuState: public GameState
{
private:

	Font* font;
	Font* font2;

	Texture* background;
	SDL_Rect bckgrndRect;

	string op1;
	string op2;
	string op3;
	string op4;

	Texture* op1Tex;
	Texture* op2Tex;
	Texture* op3Tex;
	Texture* op4Tex;
	Texture* EspTex;
	Texture* BarraTex;
	Texture* EngTex;

	SDL_Rect op1Rect;
	SDL_Rect op2Rect; 
	SDL_Rect op3Rect;
	SDL_Rect op4Rect;
	SDL_Rect EspRect;
	SDL_Rect BarraRect;
	SDL_Rect EngRect;

	SDL_Color white = { COLOR(0xF615E0ff)};
	SDL_Color blue = { COLOR(0x34D6F6ff) };
	SDL_Color black = { COLOR(0x000000ff) };

	SDL_Point mouse;
	int selectedOp = 0;

public:
	MainMenuState();
	virtual ~MainMenuState();
	
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	virtual void render();
	void changeColors();
	static void playState(Game* game,bool tutorial);
	static void exitGame(Game* game);
};

