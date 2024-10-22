#pragma once
//#include "checkML.h"
#include "GameObject.h"

enum class HookStatus { EXTEND, FAIL, EMPTY , STOP, MOVE_ENEMY, MOVE_MC};
class Hook : public GameObject
{
private:
	Vector2D originPosition;
	Vector2D hookDirection;
	float hookLength;
	HookStatus hs;
	float angle;
public:
	Hook(float hookLength);
	virtual ~Hook();
	float getLength() { return hookLength; }
	Vector2D getOriginPosition() { return originPosition; }
	Vector2D getHookDirection() { return hookDirection; }
	void setOriginPosition(Vector2D pos) { originPosition = pos; }
	void setHookDirection(Vector2D dir) { transform.velocity.set(dir); }
	HookStatus getHookStatus() { return hs; }
	void setHookStatus(HookStatus hs) { this->hs = hs; }
	float getAngle() { return angle; }
	void setAngle(float a) { angle = a; }
};

