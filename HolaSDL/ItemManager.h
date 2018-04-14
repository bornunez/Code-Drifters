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
	void AddItem(ItemPool pool,Vector2D position);
	void PickItem(ItemObject* item);
	void DeleteItem(ItemObject* item);


	void render();
	void init();
	void reset();

	vector<ItemObject*> getItems() { return items; }
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

