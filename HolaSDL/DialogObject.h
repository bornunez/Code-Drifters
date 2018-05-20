#pragma once
//#include "checkML.h"
#include "GameObject.h"
#include <vector>
#include <string>
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include "Font.h"

using namespace std; 
class Game;
class DialogObject: public GameObject
{
private:
	int pjNum;
	vector<Texture*>pjSprites;
	vector<string>names;
	Texture* nameTex;
	SDL_Rect namesRect;
	SDL_Rect pjRect;

	Font* font;

	Texture* box;
	SDL_Rect boxRect;

	int dialogNum;
	int currentPhrase;
	int currentPj;
	vector<SDL_Rect>linesRect;
	vector<Texture*>linesTex;
	vector<string>lines;
	string currentText;
	ifstream read;

	void divideText();
	void adjustRects();

	Texture* instruccion;
	SDL_Rect instruccionRect;

public:
	DialogObject(string filename);
	virtual ~DialogObject();

	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);

};

