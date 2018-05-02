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
								e->setInvincibility(true);
								//Mandar mensaje de collision bala / enemigo
								//Habria que cambiar el 1000 por el tiempo del arma
								MCBulletStun msg(2.5);
								e->sendMessage(&msg);
							}
							i++;
						}
					}
				}
				break;
			}
			//COLISION CON JUGADOR
			case BulletType::GunnerBullet:
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
							mc->setInvincibility(true);
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
						e->setInvincibility(true);
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
						boss->setInvincibility(true);
						MCAttackDamage msg(damage);
						boss->sendMessage(&msg);
						hit = true;
					}
				}
			}
		}
	}

	layerCollisions(mc);

}

void CollisionsManager::enemyCollisions()
{
	list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
	for (Enemy* e : enemies) {
		if (e->isActive()) {
			layerCollisions(e);
		}
	}
}

void CollisionsManager::hookCollisions()
{
	MainCharacter* mc = PlayState::getInstance()->getMainCharacter();
	Hook hook = mc->getHook();
	if (hook.isActive()) {//Solo mira las colisiones si el gancho está activo
		if (hook.getHookStatus() == HookStatus::EXTEND) {
			list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
			SDL_Rect hookColl = mc->getHook().getTransform()->body;
			for (GameObject* e : enemies) {//Itera la lista de enemigos activos
				if (!e->getInvincibility()) {//Solo puede atacar si son vulnerables
					vector<SDL_Rect> enemyHurtboxes = e->getCurrentAnimation()->getCurrentFrame()->getHurtboxes();
					bool hit = false;
					uint i = 0;
					while (!hit && i < enemyHurtboxes.size()) {//Itera sobre las hurtboxes del enemigo				
						if (CollisionHandler::RectCollide(enemyHurtboxes[i], hookColl)) {//Comprueba la colisión del gancho con las hurtbox					

							HookEnemyMessage msg(static_cast<Enemy*>(e));
							mc->sendMessage(&msg);
							e->setMovable(false);
						}
						i++;
					}
				}
			}
		}


		if (hook.getHookStatus() == HookStatus::EXTEND) {//Solo hace las comprobaciones del gancho con la pared si no está enganchado ya
			//Colisionamos
			Room* currRoom = LevelManager::getInstance()->getCurrentRoom();
			bool collision = false;
			vector<string> collisionsLayer = hook.getCollisionsLayers();

			vector<string>::iterator it;
			for (it = collisionsLayer.begin(); it != collisionsLayer.end() && !collision; it++) {
				TileLayer* tl = static_cast<TileLayer*>(currRoom->getMap()->GetLayer(*it));
				if (tl != nullptr) {
					if (CollisionHandler::Collide(hook.getTransform(), tl)) {//Si colisiona el gancho con las paredes cambia a MOVE_MC
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
							mc->setInvincibility(true);
							//Mandar mensaje de collision stalker / player
							Message msg(STALKER_ATTACK);
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
						mc->setInvincibility(true);
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
		layerCollisions(boss);

		if (dynamic_cast<Boss2*>(boss)->returnWheelSize() != 0)
		{
			vector<Wheel*> wheels = dynamic_cast<Boss2*>(boss)->returnWheel();
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
									mc->setInvincibility(true);
									//Mandar mensaje de collision stalker / player
									Message msg(WHEEL_HIT);
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