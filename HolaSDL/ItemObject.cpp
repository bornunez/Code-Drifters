#include "ItemObject.h"
#include "ItemManager.h"

ItemObject::ItemObject(Texture * tex, ItemType type) : GameObject(tex, PlayState::getInstance()->getMainCharacter()->getTransform()->position,10,10), type(type)
{
}

ItemObject::~ItemObject()
{
}


