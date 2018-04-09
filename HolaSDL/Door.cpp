#include "Door.h"

Door::Door(Direction dir, SDL_Rect trigger, Vector2D entry): dir(dir), trigger(trigger), entry(entry)
{
}

Door::Door()
{
}

Door::~Door()
{
}
