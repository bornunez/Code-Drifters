#pragma once
//#include "checkML.h"
#include "GameObject.h"

//Tipo de la bala
enum class BulletType { MCBullet, GunnerBullet, TurretBullet, BossBullet, BombBullet};
class Bullet : public GameObject
{
private:
	BulletType type;
	float angle;
	float damage;
public:
	Bullet(Texture * tex, bool active, BulletType type);
	Bullet(Texture * tex, Transform t, bool active, BulletType type);
	Bullet(Texture * tex, int x, int y, int width, int height, bool active, BulletType type);
	BulletType getType(){ return type; }
	virtual ~Bullet();

	void setDamage(float dmg) { damage = dmg; }
	float getDamage() { return damage; }
	float getAngle() { return angle; }
	void setAngle(float a) { angle = a; }
};