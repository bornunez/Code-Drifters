#pragma once
#include<vector>
#include<fstream>
#include<string>
#include "Texture.h"

using namespace std;
class ShopState;
struct Habilidad {
	bool bought;
	int needed_point,
		id;
	string description;
	SDL_Rect destRect;
	Texture* text;
	Texture* HLineToFather,
		*VLineToFather;

	//Button* activator;
};

class SkillTree
{
private:
	/*bool state_; //true if unlocked
	int needed_points_,
		id_; //to recognize a tree
	string description_;*/
	Habilidad skill;
	vector<SkillTree*> sons_; 	//undefined number of sons
	SkillTree* parent_; //to check information

	SDL_Renderer* rending = nullptr;
	ShopState* shopState;

	//SDL_Rect destRec;
	string FindParentID();
	void DrawLine();
	void LoadLineTex();
	int getRootID();
	void effect();

public:
	SkillTree(SkillTree* parent, string source, string TextSource, ShopState* shopState);
	~SkillTree() {};

	void HandleEvents(SDL_Event e);
	void render(SDL_Rect destination, int size, int TotalWidth);

	void AddChild(SkillTree* son) { sons_.push_back(son);};
	SkillTree* FindSon(int id);

	SDL_Rect GetSkillRect();
	void Buy();
	void UpdateBox();
	void DesactiveBox();

	//check if its unlockable
	bool Available(int money) { return (parent_->skill.bought && money >= skill.needed_point); };
	bool Unlocked() { return skill.bought; };
	int TreeHeight();
	int GetNeededPoints() { return skill.needed_point; };
	string GetDescription() { return skill.description; };
	int GetID() { return skill.id; };
	void SetUnlocked(int& n) { if (Available(n) && skill.bought == false) skill.bought = true; n -= skill.needed_point; };
};



