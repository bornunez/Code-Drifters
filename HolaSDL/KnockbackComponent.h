#pragma once
#include "UpdateComponent.h"
#include <vector>
#include <string>
using namespace std;
class KnockbackComponent :
	public UpdateComponent
{
public:
	KnockbackComponent(GameObject* o, int knockbackForce);
	KnockbackComponent(GameObject * o, int knockbackForce, string layer);
	KnockbackComponent(GameObject * o, int knockbackForce, vector<string> collisionsL);
	void update();
	void knockback(Vector2D direction);
	virtual ~KnockbackComponent();
	virtual void receiveMessage(Message* msg);
private:
	int force;
	vector<string> collisionsLayer;
};
