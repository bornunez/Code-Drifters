#pragma once
#include"SkillTree.h"
#include<vector>

//using namespace std;

class Shop
{
private:
	//Button* Left, *Right;
	SDL_Renderer* rend;
	SkillTree* Skills_[3];
	//where the 3 trees will be rendered
	Texture* fondos_[3];
	SDL_Rect right_tree,
		central_tree,
		left_tree;
	//the selected skill in a tree
	SDL_Rect cursor;
    int actual_tree = 0;
	
	bool LoadTextures();
	//to change between different trees
	void GoLeft() { actual_tree = (actual_tree + 1) % 3; };
	void GoRight() { actual_tree--; if (actual_tree < 0)actual_tree = 2;};
public:
	Shop(SDL_Renderer* ren);
	~Shop();
	
	void update();
	void render();
	void HandleEvents(SDL_Event& e);
};

