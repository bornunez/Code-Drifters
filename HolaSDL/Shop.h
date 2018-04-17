#pragma once
#include"SkillTree.h"
#include"GameObject.h"
#include<vector>

//using namespace std;

class Shop: public GameObject
{
private:
	//Button* Left, *Right;
	SkillTree* Skills_[3];
	ShopState* shopState_;
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
	Shop(ShopState* shopState);
	virtual ~Shop();
	
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);
};

