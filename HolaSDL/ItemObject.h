#pragma once
#include "GameObject.h"
#include "SimpleAnimationComponent.h"
enum ItemType { ShockWave, BulletShield, LifeItem };

class ItemObject: public GameObject
{
private:
	ItemType type;
public:

	ItemObject(Texture* tex, ItemType type);
	~ItemObject();
	ItemType getType() {return type;};
};

class LifeItemObject : public ItemObject {
public:
	LifeItemObject(Texture* tex, int life) : ItemObject(tex, LifeItem) { addComponent(new SimpleAnimationComponent(this, tex)); };
	int life;
private:
};

