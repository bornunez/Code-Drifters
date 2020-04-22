#include "MCUltimateInput.h"
#include "MainCharacter.h"
#include "EnemyManager.h"
#include "ResourceManager.h"
#include "Usabilidad/Tracker.h"

MCUltimateInput::MCUltimateInput(MainCharacter* o) : InputComponent(o), mc(o)
{
}

void MCUltimateInput::handleEvents(SDL_Event & e)
{
	if (mc->getUltiCharge() >= 100) {
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r) {

			if (mc->getMCState() == MCState::Idle || mc->getMCState() == MCState::Run || mc->getMCState() == MCState::DashEnd) {
			
				ResourceManager::getInstance()->getSoundEffect(UltiSound)->play();
				MCUltimateDamage ulti(mc->getAttackDamage(MCAttackType::ULTIMATE));
				list<Enemy*> enemies = EnemyManager::getInstance()->getActiveEnemies();
				for (GameObject* e : enemies) {//Manda el mensaje de ultimate a todos los enemigos activos
					if (!e->isDead()) {
						e->sendMessage(&ulti);//El mensaje lo recibe el damageableEnemyComponent
					}
				}
				MasterBoss* boss = EnemyManager::getInstance()->getActiveBoss();
				if (boss != nullptr) {
					if (!boss->isDead()) {
						boss->sendMessage(&ulti);//El mensaje lo recibe el damageableBossComponent
					}
				}
				mc->setMCState(MCState::Ultimate);
				mc->sendMessage(&ulti);
				mc->setUltiCharge(0);

				//TELEMETRIA
				//Evento ULTI
				Tracker::getInstance()->TrackEvent(Tracker::getInstance()->GenerateAtackEvent(ULTI));
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
