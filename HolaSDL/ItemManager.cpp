#include "ItemManager.h"

ItemManager* ItemManager::instance = nullptr;

ItemManager::ItemManager()
{
	if (items.size() > 0)
	{
		for (int i = 0; i < items.size(); i++)
		{
			if (items[i] != nullptr) items[i] = nullptr;
		}
	}
}


ItemManager::~ItemManager()
{
}

void ItemManager::AddItem(ItemPool pool)
{
	vector<ItemType> currentPool = pools[(int)pool];
	ItemType item = currentPool[Random::randomInt(0, currentPool.size()-1)];

		
	ItemObject* itemO;
	switch (item)
	{
	case ShockWave:
		//Añadimos la textura del shocwave...
		// tex = ResourceManager::getInstance()->getTexture(ShockWave);
		break;
	case BulletShield:
		itemO = new ItemObject(nullptr, item);
		break;
	case LifeItem:
		int min = 25;
		int max = 50;
		int rando = Random::randomInt(25, 50);
		if (rando >= ((max + min) / 2))
		itemO =  new LifeItemObject(ResourceManager::getInstance()->getTexture(MCBullet), rando);
		else
		itemO = new LifeItemObject(ResourceManager::getInstance()->getTexture(GunnerBullet), rando);
		break;
	}
	items.push_back(itemO);
	//prota->addComponent
}

void ItemManager::PickItem(ItemObject item)
{
	switch (item.getType())
	{
	case ItemType::ShockWave:
		//prota->addComponent(new ShockWave());
		break;
	case ItemType::BulletShield:
		break;
	case LifeItem:
		MainCharacter* prota;
		prota = PlayState::getInstance()->getMainCharacter();
		prota->addHP(static_cast<LifeItemObject*>(&item)->life);
		break;
	default:
		break;
	}
}

void ItemManager::DeleteItem(ItemObject* item)
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i] == item)
		{
			items[i] = nullptr;
		}
	}
}

void ItemManager::render()
{
	for (ItemObject* i : items) {
		if (i->isActive())
			i->render();
	}
}

void ItemManager::init()
{
	prota = PlayState::getInstance()->getMainCharacter();
}

ItemManager * ItemManager::getInstance()
{
	if (instance == nullptr)
		instance = new ItemManager();
	return instance;
}
