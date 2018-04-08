#pragma once
#include "GameObject.h"

//Tipo de la bala
enum BulletType { MCBullet, GunnerBullet, TurretBullet};
class Bullet : public GameObject
{
private:
	BulletType type;
public:
	Bullet(Texture * tex, bool active, BulletType type);
	Bullet(Texture * tex, Transform t, bool active, BulletType type);
	Bullet(Texture * tex, int x, int y, int width, int height, bool active, BulletType type);
	BulletType getType(){ return type; }
	~Bullet();

};