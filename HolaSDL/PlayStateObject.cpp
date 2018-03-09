#include "PlayStateObject.h"

PlayStateObject::PlayStateObject(PlayState * playState) : GameObject()
{
	this->playState = playState;
}

PlayStateObject::PlayStateObject(PlayState * playState, Texture * tex, Transform t, bool active) : GameObject(tex, t, active)
{
	this->playState = playState;
}

PlayStateObject::PlayStateObject(PlayState * playState, Texture * tex, Vector2D position, float bodyHeight, float bodyWidth, bool active) :
								GameObject(tex, position, bodyHeight, bodyWidth, active)
{
	this->playState = playState;
}

PlayStateObject::PlayStateObject(PlayState * playState,Texture * tex, int x, int y, int bodyHeight, int bodyWidth, bool active) :
	GameObject(tex, x, y, bodyHeight, bodyWidth, active)
{
	this->playState = playState;
}
