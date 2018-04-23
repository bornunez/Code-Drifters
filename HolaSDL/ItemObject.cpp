#include "ItemObject.h"
#include "ItemManager.h"

ItemObject::ItemObject(Texture * tex, ItemType type) : GameObject(tex, 0,0,10,10), type(type)
{
}

ItemObject::~ItemObject()
{
}


