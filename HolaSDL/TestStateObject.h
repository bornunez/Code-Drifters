#pragma once
#include "GameObject.h"

class TestState;

class TestStateObject : public GameObject
{
private:
	TestState * testState = NULL;

public:
	TestStateObject(TestState* testState, Game* game);
	TestStateObject(TestState* testState, Game* game, Texture* tex, Transform t, bool active);
	TestStateObject(TestState* testState, Game* game, Texture* tex, Vector2D position, float bodyHeight, float bodyWidth, bool active);
	TestStateObject(TestState* testState, Game* game, Texture* tex, int x, int y, int bodyHeight, int bodyWidth, bool active = true);

	TestState * getTestState() { return testState; };
};
