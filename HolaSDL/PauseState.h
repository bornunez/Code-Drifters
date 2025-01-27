#pragma once
//#include "checkML.h"
#include "UpperGameState.h"
#include "Font.h"
#include "Texture.h"
class PauseState :
	public UpperGameState
{
private:
	Font * font;
	Font* font2;

	Texture * background;
	SDL_Rect bckgrndRect;

	string op1;
	string op2;
	string op3;
	string pause;

	Texture* op1Tex;
	Texture* op2Tex;
	Texture* op3Tex;

	SDL_Rect op1Rect;
	SDL_Rect op2Rect;
	SDL_Rect op3Rect;

//	Texture* title2;
	Texture* title1;

	SDL_Rect title1Rect;
//	SDL_Rect title2Rect;

	SDL_Color white;
	SDL_Color blue;

	Texture* soundOff;
	Texture* soundOn;
	SDL_Rect muteRect;

	SDL_Point mouse;
	int selectedOp = 0;
public:
	PauseState(GameState* upper);
	virtual ~PauseState();
	virtual void handleEvent(SDL_Event& e);
	virtual void update();
	virtual void render();
	void changeColors();
	static void exitGame(Game* game);
};

