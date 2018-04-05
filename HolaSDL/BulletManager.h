#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "GameObject.h"

class BulletManager : public GameObject {
private:
	Bullet * getBullet();
	virtual void receive(Message* msg);
	virtual void shoot(GameObject* owner, Vector2D position, Vector2D velocity);
	std::vector<Bullet*> bullets;
	//FillRectRenderer bulletRenderer;
	//BasicMotionPhysics bulletPhysics;

public:
	BulletManager();
	~BulletManager();
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);
	 std::vector<Bullet*>& getBullets();
};
