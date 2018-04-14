#include "ItemManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Game.h"
#include "Camera.h"
#include "SkeletonRenderer.h"

ItemManager* ItemManager::instance = nullptr;

ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

void ItemManager::AddItem(ItemPool pool, Vector2D position)
{
	vector<ItemType> currentPool = pools[(int)pool];
	ItemType item = currentPool[Random::randomInt(0, currentPool.size()-1)];

		
	ItemObject* itemO = nullptr;
	switch (item)
	{
	case ShockWave:
		//Añadimos la textura del shocwave...
		// tex = ResourceManager::getInstance()->getTexture(ShockWave);
		break;
	case BulletShield:
		itemO = new ItemObject(nullptr, item);
		break;
	case LifeItem: {
		int min = 25;
		int max = 50;
		int rando = Random::randomInt(25, 50);
		if (rando >= ((max + min) / 2))
			itemO = new LifeItemObject(ResourceManager::getInstance()->getTexture(MCBullet), rando);
		else
			itemO = new LifeItemObject(ResourceManager::getInstance()->getTexture(GunnerBullet), rando);
		break;
	}
	default:
		itemO = nullptr;
		break;
	}
	//Y lo dropeamos
	if (itemO != nullptr) {
		Transform* t = itemO->getTransform();
		t->position.set(position);
		t->body.x = t->position.getX(); t->body.y = t->position.getY();
		t->body.w = t->body.h = 50;
		items.push_back(itemO);
	}
	//prota->addComponent
}

void ItemManager::PickItem(ItemObject* item)
{
	MainCharacter* prota;
	prota = PlayState::getInstance()->getMainCharacter();
	switch (item->getType())
	{
	case ItemType::ShockWave:
		//prota->addComponent(new ShockWave());
		cout << "Añadiendo [ SHOCKWAVE ] Vida" << endl;
		break;
	case ItemType::BulletShield:
		cout << "Añadiendo [ BULLETSHIELD ] Vida" << endl;
		break;
	case LifeItem:
		prota->addHP(static_cast<LifeItemObject*>(item)->life);
		cout << "Añadiendo  [ " << static_cast<LifeItemObject*>(item)->life << " ] Vida"<< endl;
		break;
	default:
		break;
	}
	DeleteItem(item);
}

void ItemManager::DeleteItem(ItemObject* item)
{
	item->setActive(false);
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

void ItemManager::reset()
{
	while (!items.empty())
	{
		items.pop_back();
	}
}

ItemManager * ItemManager::getInstance()
{
	if (instance == nullptr)
		instance = new ItemManager();
	return instance;
}
