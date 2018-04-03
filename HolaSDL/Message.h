#ifndef MESSAGE_H_
#define MESSAGE_H_

//USAR PARA MENSAJES CON ARGUMENTOS
enum MessageId {
	EXAMPLEMSG,
	KNOCK_BACK,
	MC_ATTACK_DAMAGE
};

struct Message {
	Message(MessageId id) :
		id(id) {
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

#endif /* MESSAGE_H_ */