#pragma once
#include "checkML.h"
#include "GameObject.h"
#include "Bullet.h"
#include "GameObject.h"

class BulletManager : public GameObject {
private:
	Bullet * getBullet(BulletType bulletType);
	virtual void receive(Message* msg);
	std::vector<Bullet*> bullets;
	//FillRectRenderer bulletRenderer;
	//BasicMotionPhysics bulletPhysics;

	//Singleton
	static BulletManager* instance;
	BulletManager();

public:
	//Singleton
	static BulletManager* getInstance() { return instance; }
	static void createInstance();
	static void ResetInstance();

	~BulletManager();
	virtual void update();
	virtual void render();
	virtual void handleEvents(SDL_Event& e);
	std::vector<Bullet*>& getBullets();
	void shoot(GameObject* owner, Vector2D position, Vector2D velocity, BulletType bulletType);
	void shoot(GameObject* owner, Transform bulletTransform, BulletType bulletType);
};
