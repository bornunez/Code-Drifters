#ifndef MESSAGE_H_
#define MESSAGE_H_

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
	STALKER_ATTACK,



	//Con argumentos
	EXAMPLEMSG,
	KNOCK_BACK,
	MC_ATTACK_DAMAGE,
	BULLET_CREATED,
	MC_BULLET_COLLISION,
	ENEMY_BULLET_COLLISION,


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
struct MCBulletStun : Message {
	MCBulletStun(int stunTime) : Message(MC_BULLET_COLLISION), stunTime(stunTime) {}
	float stunTime;
};

#endif /* MESSAGE_H_ */