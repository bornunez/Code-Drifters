#ifndef MESSAGE_H_
#define MESSAGE_H_
class GameObject;
class Enemy;
//USAR PARA MENSAJES CON ARGUMENTOS
enum MessageId {
	//Idle
	IDLE_LEFT,
	IDLE_RIGHT,
	IDLE_TOP,
	IDLE_BOT,
	IDLE_TOPLEFT,
	IDLE_TOPRIGHT,
	IDLE_BOTLEFT,
	IDLE_BOTRIGHT,
	//Run
	RUN_LEFT,
	RUN_RIGHT,
	RUN_TOP,
	RUN_BOT,
	//MainCharacter Attack
	ATTACK1_LEFT,
	ATTACK2_LEFT,
	ATTACK3_LEFT,
	ATTACK1_RIGHT,
	ATTACK2_RIGHT,
	ATTACK3_RIGHT,
	ATTACK1_TOPLEFT,
	ATTACK2_TOPLEFT,
	ATTACK3_TOPLEFT,
	ATTACK1_TOPRIGHT,
	ATTACK2_TOPRIGHT,
	ATTACK3_TOPRIGHT,
	ATTACK1_BOTLEFT,
	ATTACK2_BOTLEFT,
	ATTACK3_BOTLEFT,
	ATTACK1_BOTRIGHT,
	ATTACK2_BOTRIGHT,
	ATTACK3_BOTRIGHT,
	ATTACKCHARGING,
	ATTACKCHARGED,
	FULLCHARGE,
	MC_SHOT,
	MC_HOOKSHOT,
	ULTIMATE,

	//Death
	MC_DEATH,
	ACID_DEATH,

	//GameObjects
	HURT,
	ENEMY_DEATH,
	GUN_STUN,
	STUN_OFF,
	ENEMY_SPAWN,
	ENEMY_ATTACK,

	//Gunner Shot
	SHOT_LEFT,
	SHOT_RIGHT,
	SHOT_TOP,
	SHOT_BOT,
	SHOT_TOPRIGHT,
	SHOT_TOPLEFT,
	SHOT_BOTRIGHT,
	SHOT_BOTLEFT,

	//Stalker
	STALKER_RUN,
	STALKER_CHARGE,
	STALKER_ATTACK,

	//Turret
	TURRET_IDLE,
	TURRET_ALERT,
	TURRET_ALERT_OVER,

	//Charger
	CHARGE_BOT, CHARGE_RIGHT, CHARGE_TOP, CHARGE_LEFT,
	PRECHARGE_BOT, PRECHARGE_RIGHT, PRECHARGE_TOP, PRECHARGE_LEFT,
	STUN,

	//Con argumentos
	EXAMPLEMSG,
	KNOCK_BACK,
	MC_ATTACK_DAMAGE,
	BULLET_CREATED,
	MC_BULLET_COLLISION,
	ENEMY_BULLET_COLLISION,
	HIT_WALL,

	//Gancho
	HOOK_ENEMY,
	HOOK_WALL,
	HOOK_EXTEND,
	HOOK_FAIL,
	HOOK_EMPTY,
	HOOK_STOP,

	//Boss1
	BOSS1_ATTACK,
	//Wheels
	WHEEL_HIT,
	BOSS_BULLET_HIT,

	//Sala
	ROOM_ENTER,
	ROOM_EXIT,

	//ID para crear mensajes vacios e inicializarlos con una ID mas tarde
	NO_ID
};

struct Message {
	Message(MessageId id = NO_ID) : id(id) 
	{
	}
	MessageId id;
};

struct exampleMSG : Message {
	exampleMSG() :
		Message(EXAMPLEMSG) {}
	//Argumento1* arg;
	//Argumento2* arg;
};


struct KnockbackMessage : Message {
	KnockbackMessage(Vector2D knock) : Message(KNOCK_BACK), knockback(knock) {}
	Vector2D knockback;
};

struct MCAttackDamage : Message {
	MCAttackDamage(float dmg) : Message(MC_ATTACK_DAMAGE), damage(dmg) {}
	float damage;
};
struct MCUltimateDamage : Message {
	MCUltimateDamage(float dmg) : Message(ULTIMATE), damage(dmg) {}
	float damage;
};
struct MCBulletStun : Message {
	MCBulletStun(int stunTime, float dmg) : Message(MC_BULLET_COLLISION), stunTime(stunTime), damage(dmg) {}
	int stunTime;
	float damage;
};

struct HookEnemyMessage : Message {
	HookEnemyMessage(Enemy* o) : Message(HOOK_ENEMY), gameObject(o){}
	Enemy* gameObject;
};
struct EnemyAttackMessage : Message {
	EnemyAttackMessage(float dmg) : Message(ENEMY_ATTACK), damage(dmg) {}
	float damage;
};
struct EnemyBulletMessage : Message {
	EnemyBulletMessage(float dmg) : Message(ENEMY_BULLET_COLLISION ), damage(dmg){}
	float damage;
};
struct BossBulletMessage : Message {
	BossBulletMessage(float dmg) : Message(BOSS_BULLET_HIT), damage(dmg) {}
	float damage;
};

struct BossAttack : Message
{
	BossAttack(float dmg) : Message(BOSS1_ATTACK), damage(dmg) {}
	int damage;
};
struct WheelHit : Message
{
	WheelHit(float dmg) : Message(WHEEL_HIT), damage(dmg) {}
	int damage;
};
#endif /* MESSAGE_H_ */