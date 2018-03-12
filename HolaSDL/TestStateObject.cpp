#include "TestStateObject.h"

TestStateObject::TestStateObject(TestState * testState, Game * game) : GameObject(game)
{
	this->testState = testState;
}

TestStateObject::TestStateObject(TestState * testState, Game * game, Texture * tex, Transform t, bool active) : GameObject(game, tex, t, active)
{
	this->testState = testState;
}

TestStateObject::TestStateObject(TestState * testState, Game * game, Texture * tex, Vector2D position, float bodyHeight, float bodyWidth, bool active) :
	GameObject(game, tex, position, bodyHeight, bodyWidth, active)
{
	this->testState = testState;
}

TestStateObject::TestStateObject(TestState * testState, Game * game, Texture * tex, int x, int y, int bodyHeight, int bodyWidth, bool active) :
	GameObject(game, tex, x, y, bodyHeight, bodyWidth, active)
{
	this->testState = testState;
}
