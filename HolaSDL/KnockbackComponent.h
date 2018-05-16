#pragma once
//#include "checkML.h"
#include "UpdateComponent.h"
#include <vector>
#include <string>
using namespace std;
class KnockbackComponent :
	public UpdateComponent
{
public:
	KnockbackComponent(GameObject* o, int knockbackForce);
	void update();
	void knockback(Vector2D direction);
	virtual ~KnockbackComponent();
	virtual void receiveMessage(Message* msg);
private:
	int force;
};
