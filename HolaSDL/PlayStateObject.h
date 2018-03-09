#pragma once
#include "GameObject.h"

class PlayState;

class PlayStateObject : public GameObject
{
private:
	PlayState * playState = NULL;

public:
	PlayStateObject(PlayState* playState);
	PlayStateObject(PlayState* playState, Texture* tex, Transform t, bool active);
	PlayStateObject(PlayState* playState, Texture* tex, Vector2D position, float bodyHeight, float bodyWidth, bool active);
	PlayStateObject(PlayState* playState, Texture* tex, int x, int y, int bodyHeight, int bodyWidth, bool active = true);

	PlayState * getPlayState(){ return playState; };
};