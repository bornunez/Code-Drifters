#include "CollisionsManager.h"
#include "Managers.h"
#include "Room.h"
#include "Map.h"
#include "TileLayer.h"
#include "CollisionHandler.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Enemy.h"
#include "PlayState.h"
#include "ItemManager.h"
#include "ItemObject.h"
#include "Transform.h"
#include "Hook.h"
#include "ParticlesManager.h"
#include "CoinManager.h"
#include "Coin.h"
#include "Game.h"
#include "Boss2.h"

CollisionsManager* CollisionsManager::instance = nullptr;

CollisionsManager::CollisionsManager()
{


}

CollisionsManager::~CollisionsManager()
{
}

CollisionsManager * CollisionsManager::getInstance()
{
	if (instance == nullptr)
		instance = new CollisionsManager();
	return instance;
}

void CollisionsManager::ResetInstance()
{
	delete instance; 
	instance = nullptr; 
}

void CollisionsManager::handleInput(const SDL_Event & event)
{
}

void CollisionsManager::update()
{
	//COLISIONES DEL PLAYER
	playerCollisions();


	//COLISIONES DE LAS BALAS
	bulletCollisions();


	//COLISIONES DE LOS ENEMIGOS
	enemyCollisions();

	//COLISIONES DEL GANCHO
	hookCollisions();

	//COLISION STALKER CON MC
	if(PlayState::getInstance()->getMainCharacter()->getMCState() != MCState::Hurt)
		enemyAttackCollision();

	//Colision del Boss
	bossCollisions();

	//COLLISIONES DE LAS MONEDAS CON ENTORNO / PROTA
	coinCollision();
}

void CollisionsManager::render()
{
}

void CollisionsManager::bulletCollisions()
{
	//Colisionamos
	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	vector<string>::iterator it;
	vector<string> collisionsLayer = { "Paredes" };
	vector<Bullet*> bullets = BulletManager::getInstance()->getBullets();

	//Colisionamos todas las balas que esten activas
	for (Bullet* b : bullets) {
		if (b->isActive()) {
			b->updateBody();
			Transform* t = b->getTransform();

			bool hit = false;
			switch (b->getType())
			{
			case (BulletType::MCBullet):
			{ 
				//COLISION CON ENEMIGOS
				list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
				for (GameObject* e : enemies) {//Itera la lista de enemigos activos
					if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
						vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
						SDL_Rect hitbox = t->body;
						uint i = 0;
						while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo
							if (CollisionHandler::RectCollide(enemyHurtboxes[i], hitbox)) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
								hit = true;
								//Mandar mensaje de collision bala / enemigo
								//Habria que cambiar el 1000 por el tiempo del arma
								//MCBulletStun msg(2.5);
								MCBulletStun msg(PlayState::getInstance()->getMainCharacter()->getStunTime(), PlayState::getInstance()->getMainCharacter()->getAttackDamage(MCAttackType::SHOT));
								e->sendMessage(&msg);
							}
							i++;
						}
					}
				}
				if (!hit) {
					//Colision con Boss activo
					MasterBoss* boss = EnemyManager::getInstance()->getActiveBoss();
					if (boss != nullptr) {
						if (!boss->getInvincibility()) {
							vector<SDL_Rect> bossHurtboxes = boss->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
							SDL_Rect hitbox = t->body;
							uint i = 0;
							while (!hit && i < bossHurtboxes.size()) {//Itera sobre las hurtboxes del boss
								if (CollisionHandler::RectCollide(bossHurtboxes[i], hitbox)) {//Comprueba la colisión de la hitbox dela bala con las hurtboxes del boss
									hit = true;
									//Mandar mensaje de collision bala / boss
									MCBulletStun msg(PlayState::getInstance()->getMainCharacter()->getStunTime(), PlayState::getInstance()->getMainCharacter()->getAttackDamage(MCAttackType::SHOT));
									boss->sendMessage(&msg);
								}
								i++;
							}

						}
					}
				}
				break;
			}
			//COLISION CON JUGADOR
			case BulletType::GunnerBullet: case BulletType::BombBullet:
			{
				//Colisionamos la bala con las hurtboxes del player
				MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
				vector<SDL_Rect> hurtBoxes = mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
				SDL_Rect hitbox = t->body;
				int i = 0;
				while (!hit && i < hurtBoxes.size())
				{
					if (!mc->getInvincibility()) {
						if (CollisionHandler::RectCollide(hurtBoxes[i], hitbox)) {//Comprueba la colisión de la hitbox de la bala con la hurtbox del MC
							hit = true;
							//Mandar mensaje de collision bala / player
							Message msg(ENEMY_BULLET_COLLISION);
							mc->sendMessage(&msg);
							Vector2D empuje = Vector2D(b->getTransform()->direction.getX(), b->getTransform()->direction.getY());
							empuje.normalize();
							KnockbackMessage msg1(empuje);
							mc->sendMessage(&msg1);
							
						}
						
					}
					i++;
				}
			}

			case BulletType::BossBullet:
			{
				//Colisionamos la bala con las hurtboxes del player
				MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
				vector<SDL_Rect> hurtBoxes = mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
				SDL_Rect hitbox = t->body;
				int i = 0;
				while (!hit && i < hurtBoxes.size())
				{
					if (!mc->getInvincibility()) {
						if (CollisionHandler::RectCollide(hurtBoxes[i], hitbox)) {//Comprueba la colisión de la hitbox de la bala con la hurtbox del MC
							hit = true;
							//Mandar mensaje de collision bala / player
							Message msg(BOSS_BULLET_HIT);
							mc->sendMessage(&msg);
							Vector2D empuje = Vector2D(b->getTransform()->direction.getX(), b->getTransform()->direction.getY());
							empuje.normalize();
							KnockbackMessage msg1(empuje);
							mc->sendMessage(&msg1);

						}

					}
					i++;
				}
			}
			default:
				break;
			}


			bool collision = false;
			//COLISION CON PAREDES
			for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
				TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
				if (tl != nullptr) {
					if (CollisionHandler::Collide(t, tl)) {
						collision = true;
					}
				}
			}
			if (collision || hit) {
				Particle* p = ParticlesManager::getInstance()->getParticle(ParticleType::GunnerBulletExplosion, b->getCenterPos().getX(), b->getCenterPos().getY());
				
				b->setActive(false);
			}
		}
	}
}

void CollisionsManager::playerCollisions()
{
	vector<ItemObject*> items = ItemManager::getInstance()->getItems();
	//Colisionamos la bala con las hurtboxes del player
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
	for (ItemObject* item : items) {
		if (item->isActive() && CollisionHandler::RectCollide(mc->getTransform()->body, item->getTransform()->body)) {
			//Mandar mensaje a mc
			ItemManager::getInstance()->PickItem(item);
		}
	}


	////Colision jugador con enemigos activos, sin hurt

	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	for (GameObject* e : enemies) {//Itera la lista de enemigos activos
		if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
			vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
			vector<SDL_Rect> hitboxes = mc->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
			bool hit = false;
			uint i = 0;
			while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo
				uint j = 0;
				while (!hit && j < hitboxes.size()) {
					if (CollisionHandler::RectCollide(enemyHurtboxes[i], hitboxes[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
						Vector2D empuje = Vector2D(mc->getTransform()->direction.getX(), mc->getTransform()->direction.getY());
						empuje.normalize();
						KnockbackMessage msg1(empuje);
						e->sendMessage(&msg1);
						float damage = mc->getAttackDamage(mc->getCurrentAttackType());//El valor de ataque del jugador
						if(mc->isLifeStealEnable())
							mc->addHP(damage * mc->getLifeSteal() / 100);
						MCAttackDamage msg2(damage);
						e->sendMessage(&msg2);
						hit = true;
					}
					j++;
				}
				i++;
			}
		}
	}

	//Colision con Boss activo
	MasterBoss* boss = EnemyManager::getInstance()->getActiveBoss();
	if (boss != nullptr) {
		if (!boss->getInvincibility()) {
			MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
			bool hit = false;
			vector<SDL_Rect> bossHurtboxes = boss->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
			vector<SDL_Rect> mcHitboxes = mc->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
			uint i = 0;

			//Itera sobre las hitboxes del enemigo por cada HurtBox del MC
			for (uint i = 0; !hit && i < bossHurtboxes.size(); i++) {
				for (uint j = 0; !hit && j < mcHitboxes.size(); j++) {
					if (CollisionHandler::RectCollide(bossHurtboxes[i], mcHitboxes[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo

						float damage = mc->getAttackDamage(mc->getCurrentAttackType());//El valor de ataque del jugador
						if (mc->isLifeStealEnable())
							mc->addHP(damage * mc->getLifeSteal() / 400);
						MCAttackDamage msg(damage);
						boss->sendMessage(&msg);
						hit = true;
					}
				}
			}
		}
	}
	overlapCollisions(mc);
	layerCollisions(mc);

}

void CollisionsManager::enemyCollisions()
{
	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	for (Enemy* e : enemies) {
		if (e->isActive()) {
			if (!e->isDead()) {
				overlapCollisions(e);
				layerCollisions(e);
				if (e->getEnemyState() != EnemyState::Hooked) {
					acidCollisions(e);
				}
			}
		}
	}
}

void CollisionsManager::acidCollisions(Enemy* e)
{
	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	vector<string> collisionsLayer = { "Acido" };
	bool collision = false;

	vector<string>::iterator it;
	for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
		TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
		if (tl != nullptr) {
			if (CollisionHandler::Collide(e->getTransform(), tl)) {//Si colisiona el gancho con las paredes cambia a MOVE_MC
				collision = true;
				Message msg(ACID_DEATH);
				e->sendMessage(&msg);
			}
		}
	}

}

void CollisionsManager::hookCollisions()
{
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
	Hook* hook = mc->getHook();
	if (hook->isActive()) {//Solo mira las colisiones si el gancho está activo
		if (hook->getHookStatus() == HookStatus::EXTEND) {
			list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
			SDL_Rect hookColl = mc->getHook()->getTransform()->body;
			for (Enemy* e : enemies) {//Itera la lista de enemigos activos
				if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
					vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
					bool hit = false;
					uint i = 0;
					while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo				
						if (CollisionHandler::RectCollide(enemyHurtboxes[i], hookColl)) {//Comprueba la colisión del gancho con las hurtbox					
							if (e->isHookable()) {
								//METER SONIDO DE FUISTE COGIDO BOLUDO
								ResourceManager::getInstance()->getSoundEffect(HookHit)->playChannel(7, 0);
								HookEnemyMessage msg(static_cast<Enemy*>(e));
								mc->sendMessage(&msg);
								e->setMovable(false);
							}
							else {
								//METER SONIDO DE GANCHO FALLO BOLUDO
								ResourceManager::getInstance()->getSoundEffect(HookMiss)->playChannel(7, 0);
								Message msg(HOOK_STOP);
								mc->sendMessage(&msg);
							}
						}
						i++;
					}
				}
			}

		}


		if (hook->getHookStatus() == HookStatus::EXTEND) {//Solo hace las comprobaciones del gancho con la pared si no está enganchado ya
			//Colisionamos
			Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
			bool collision = false;
			vector<string> collisionsLayer = hook->getCollisionsLayers();

			vector<string>::iterator it;
			for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
				TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
				if (tl != nullptr) {
					if (CollisionHandler::Collide(hook->getTransform(), tl)) {//Si colisiona el gancho con las paredes cambia a MOVE_MC
						collision = true;
						Message msg(HOOK_WALL);
						mc->sendMessage(&msg);
					}
				}
			}
		}		
	}
}

void CollisionsManager::layerCollisions(GameObject* o) {

	Transform* t = o->getTransform();
	vector<string> collisionsLayer = o->getCollisionsLayers();
	Vector2D prevPosition = o->getPreviousPosition();

	//Movemos al personaje y a su body
	o->updateBody();
	SDL_Rect bodyX, bodyY;
	bodyX = bodyY = t->body;
	bodyX.y = prevPosition.getY();
	bodyY.x = prevPosition.getX();

	vector<SDL_Rect> rects = { bodyX, bodyY };
	vector<bool> collisions = { false,false };
	//Colisionamos
	Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
	bool collisionX = false;
	bool collisionY = false;
	vector<string>::iterator it;
	for (it = collisionsLayer.begin(); it != collisionsLayer.end() && (!collisionX || !collisionY); it++) {
		TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
		if (tl != nullptr) {
			collisions = CollisionHandler::Collide(rects, tl);
			collisionX = collisions[0] || collisionX;
			collisionY = collisions[1] || collisionY;
		}
	}
	if (collisionX || collisionY) {
		//Si hay colision, cogemos la antigua posicion
		if (collisionX) {
			t->position.setX(prevPosition.getX());
		}
		if (collisionY){
			t->position.setY(prevPosition.getY());
		}
		//Finalmente lo notificamos
		Message msg(HIT_WALL);
		o->sendMessage(&msg);
	}
	o->updatePreviousPosition();
	o->updateBody();
}


void CollisionsManager::enemyAttackCollision() {
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	bool hit = false;
	//COLISION CON ENEMIGOS
	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	for (Enemy* e : enemies) {//Itera la lista de enemigos activos
		if (e->getEnemyState() == EnemyState::Attack) {				//Solo se comprueban colisiones si el enemigo esta atacando
			if (!mc->getInvincibility()) {
				vector<SDL_Rect> enemyHitboxes = e->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
				vector<SDL_Rect> mcHurtboxes = mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
				uint i = 0;

				//Itera sobre las hitboxes del enemigo por cada HurtBox del MC
				for (uint i = 0; !hit && i < enemyHitboxes.size(); i++) {
					for (uint j = 0; !hit && j < mcHurtboxes.size(); j++) {
						if (CollisionHandler::RectCollide(enemyHitboxes[i], mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes()[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
							hit = true;
							//Mandar mensaje de collision stalker / player
							float damage = e->getMeleeDmg();
							EnemyAttackMessage msg(damage);
							mc->sendMessage(&msg);
							Vector2D empuje = mc->getCenterPos() - e->getCenterPos();
							empuje.normalize();
							KnockbackMessage msg1(empuje);
							mc->sendMessage(&msg1);
						}
					}
				}
			}
		}
	}
}

bool CollisionsManager::overlapCollisions(GameObject* o)
{
	Transform* t = o->getTransform();
	SDL_Rect overlapBody = t->overlapCollision.overlapBody;
	GameObject* mc = PlayState::getInstance()->getMainCharacter();
	bool auxCollision = false;
	bool collision = false;


	if (mc != o) {
		if (mc->getTransform()->overlapCollision.active) {
			auxCollision = CollisionHandler::RectCollide(overlapBody, mc->getTransform()->overlapCollision.overlapBody);
			if (auxCollision) {
				collision = true;
				Vector2D empuje = o->getCenterPos() - mc->getCenterPos();
				empuje.normalize();
				t->position.set(t->position + empuje * 500 * Time::getInstance()->DeltaTime);
			}
		}
	}

	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();

	for (GameObject* e : enemies) {
		if (e != o) {
			if (!e->isDead()) {
				if (e->getTransform()->overlapCollision.active) {
					auxCollision = CollisionHandler::RectCollide(overlapBody, e->getTransform()->overlapCollision.overlapBody);
					if (auxCollision) {
						collision = true;
						Vector2D empuje = o->getCenterPos() - e->getCenterPos();
						empuje.normalize();
						t->position.set(t->position + empuje * 500 * Time::getInstance()->DeltaTime);
					}
				}
			}
		}
	}

	GameObject* boss = EnemyManager::getInstance()->getActiveBoss();
	if (boss != nullptr) {
		if (boss != o) {
			if (!boss->isDead()) {
				if (boss->getTransform()->overlapCollision.active) {
					auxCollision = CollisionHandler::RectCollide(overlapBody, boss->getTransform()->overlapCollision.overlapBody);
					if (auxCollision) {
						collision = true;
						Vector2D empuje = o->getCenterPos() - boss->getCenterPos();
						empuje.normalize();
						t->position.set(t->position + empuje * 500 * Time::getInstance()->DeltaTime);
					}
				}
			}
		}
	}
	return collision;
}

void CollisionsManager::bossCollisions()
{
	MasterBoss* boss = EnemyManager::getInstance()->getActiveBoss();
	if (boss != nullptr) {
		MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
		if (!mc->getInvincibility()) {
			bool hit = false;
			vector<SDL_Rect> bossHitboxes = boss->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
			vector<SDL_Rect> mcHurtboxes = mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
			uint i = 0;

			//Itera sobre las hitboxes del enemigo por cada HurtBox del MC
			for (uint i = 0; !hit && i < bossHitboxes.size(); i++) {
				for (uint j = 0; !hit && j < mcHurtboxes.size(); j++) {
					if (CollisionHandler::RectCollide(bossHitboxes[i], mcHurtboxes[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
						hit = true;
						//Mandar mensaje de collision stalker / player
						BossAttack msg(boss->getDamage());
						mc->sendMessage(&msg);
						Vector2D empuje = mc->getCenterPos() - boss->getCenterPos();
						empuje.normalize();
						KnockbackMessage msg1(empuje);
						mc->sendMessage(&msg1);
					}
				}
			}
		}
		if (!boss->isDead())
			layerCollisions(boss);

		if (boss->getBossType() == 2  && dynamic_cast<Boss2*>(boss)->returnWheelSize() != 0)
		{
			vector<Wheel*> wheels = dynamic_cast<Boss2*>(boss)->returnWheel();
			if (wheels.size() != 0)
			{
				MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
				Hook* hook = mc->getHook();
				for (int i = 0; i < wheels.size(); i++)
				{
					vector<SDL_Rect> wheelsHitboxes = wheels[i]->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
					vector<SDL_Rect> mcHurtboxes = mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
					if (!mc->getInvincibility()) {
						bool hit = false;
						uint i = 0;

						//Itera sobre las hitboxes del enemigo por cada HurtBox del MC
						for (uint i = 0; !hit && i < wheelsHitboxes.size(); i++) {
							for (uint j = 0; !hit && j < mcHurtboxes.size(); j++) {
								if (CollisionHandler::RectCollide(wheelsHitboxes[i], mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes()[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
									hit = true;
									//Mandar mensaje de collision stalker / player
									WheelHit msg(wheels[0]->GetDamage());
									mc->sendMessage(&msg);
									Vector2D empuje = mc->getCenterPos() - wheels[i]->getCenterPos();
									empuje.normalize();
									KnockbackMessage msg1(empuje);
									mc->sendMessage(&msg1);
								}
							}
						}
					}
					//Colisión con el gancho
					if (hook->isActive()) {//Solo mira las colisiones si el gancho está activo
						if (hook->getHookStatus() == HookStatus::EXTEND) {
							bool hit = false;
							vector<SDL_Rect> wheelsHurtboxes = wheels[i]->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
							for (uint i = 0; !hit && i < wheelsHurtboxes.size(); i++) {
								if (CollisionHandler::RectCollide(wheelsHurtboxes[i], hook->getTransform()->body)) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
									hit = true;
									ResourceManager::getInstance()->getSoundEffect(HookMiss)->playChannel(7, 0);
									Message msg(HOOK_STOP);
									mc->sendMessage(&msg);
								}
								
							}
							

						}
					}
				}
			}
		}

		if (boss->getBossType() == 3 && dynamic_cast<Boss3*>(boss)->returnWaveSize() != 0)
		{
			vector<Wave*> wheels = dynamic_cast<Boss3*>(boss)->returnwave();
			if (wheels.size() != 0)
			{
				MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
				for (int i = 0; i < wheels.size(); i++)
				{
					if (!mc->getInvincibility()) {
						bool hit = false;
						vector<SDL_Rect> wheelsHitboxes = wheels[i]->getCurrentAnimation()->getCurrentFrame()->getHitboxes();
						vector<SDL_Rect> mcHurtboxes = mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
						uint i = 0;

						//Itera sobre las hitboxes del enemigo por cada HurtBox del MC
						for (uint i = 0; !hit && i < wheelsHitboxes.size(); i++) {
							for (uint j = 0; !hit && j < mcHurtboxes.size(); j++) {
								if (CollisionHandler::RectCollide(wheelsHitboxes[i], mc->getCurrentAnimation()->getCurrentFrame()->getHurtboxes()[j])) {//Comprueba la colisión de las hitboxes de las espada con las hurtboxes del enemigo
									hit = true;
									//Mandar mensaje de collision stalker / player
									WheelHit msg(wheels[0]->GetDamage());
									mc->sendMessage(&msg);
									Vector2D empuje = mc->getCenterPos() - wheels[i]->getCenterPos();
									empuje.normalize();
									KnockbackMessage msg1(empuje);
									mc->sendMessage(&msg1);
								}
							}
						}
					}
				}
			}
		}
	}
}

void CollisionsManager::coinCollision()
{
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();

	vector<Coin*> coins = CoinManager::getInstance()->getCoins();
	for (Coin* c : coins) {
		if (c->isActive()) {
			if (c->getTransform()->speed <= 0.5) {
				if (CollisionHandler::RectCollide(c->getTransform()->body, mc->getTransform()->body)) {
					CoinManager::getInstance()->Pick(c);
				}
			}
			else
				layerCollisions(c);
		}
	}

}