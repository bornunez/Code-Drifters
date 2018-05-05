#include "MCUltimateInput.h"
#include "MainCharacter.h"
#include "EnemyManager.h"

MCUltimateInput::MCUltimateInput(MainCharacter* o) : InputComponent(o), mc(o)
{
}

void MCUltimateInput::handleEvents(SDL_Event & e)
{
	if (mc->getUltiCharge() >= 100) {
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {

			if (mc->getMCState() == MCState::Idle || mc->getMCState() == MCState::Run || mc->getMCState() == MCState::DashEnd) {
				MCAttackDamage msg(mc->getUltimateAttackDamage());
				Message ulti(ULTIMATE);
				list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
				for (GameObject* e : enemies) {//Manda el mensaje de ultimate a todos los enemigos activos
					if (!e->isDead()) {
						e->sendMessage(&msg);//El mensaje lo recibe el damageableEnemyComponent
						e->sendMessage(&ulti);
					}
				}
				MasterBoss* boss = EnemyManager::getInstance()->getActiveBoss();
				if (boss != nullptr) {
					if (!boss->isDead()) {
						boss->sendMessage(&msg);//El mensaje lo recibe el damageableBossComponent
						boss->sendMessage(&ulti);
					}
				}
				mc->setMCState(MCState::Ultimate);
				mc->sendMessage(&msg);
				mc->sendMessage(&ulti);
			}
		}
	}
}

void MCUltimateInput::receiveMessage(Message * msg)
{

}


MCUltimateInput::~MCUltimateInput()
{
}
