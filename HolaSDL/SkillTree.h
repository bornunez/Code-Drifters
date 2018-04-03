#pragma once
#include<vector>
#include<fstream>
#include<string>
#include"Button.h"

using namespace std;

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

	//Button* boton;
	//SDL_Rect destRec;
	static void Buy();
	string FindParentID();
	void DrawLine();
	int getRootID();

public:
	SkillTree(SkillTree* parent, string source, SDL_Renderer* rend, string TextSource);
	~SkillTree() {};

	void HandleEvents(SDL_Event e);
	void render(SDL_Rect destination, int size, int TotalWidth);

	void AddChild(SkillTree* son) { sons_.push_back(son);};
	SkillTree* FindSon(int id);

	//check if its unlockable
	bool Available(int money) { return (parent_->skill.bought && money >= skill.needed_point); };
	bool Unlocked() { return skill.bought; };
	int TreeHeight();
	int GetNeededPoints() { return skill.needed_point; };
	string GetDescription() { return skill.description; };
	int GetID() { return skill.id; };
	void SetUnlocked(int& n) { if (Available(n) && skill.bought == false) skill.bought = true; n -= skill.needed_point; };
};



