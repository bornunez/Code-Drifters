#pragma once
#include "ItemObject.h"
#include <vector>
#include "Random.h"
#include "PlayState.h"
#include "MainCharacter.h"
#include "ResourceManager.h"


enum ItemPool {Enemies, Bosses};

using namespace std;


class ItemManager
{
public:
	~ItemManager();
	void AddItem(ItemPool pool);
	void PickItem(ItemObject item);
	void DeleteItem(ItemObject* item);
	void render();
	void init();
	static ItemManager* getInstance();

private:
	ItemManager();
	static ItemManager* instance;
	vector<ItemObject*> items;
	vector< vector<ItemType>> pools = {
		{LifeItem	   },
		{ShockWave, BulletShield		} 
	};
	GameObject* prota;


};

