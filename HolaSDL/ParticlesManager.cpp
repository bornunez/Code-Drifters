#include "ParticlesManager.h"
#include "ResourceManager.h"
#include "Random.h"
#include "SimpleAnimationComponent.h"
#include "Game.h"
ParticlesManager* ParticlesManager::instance = nullptr;

ParticlesManager::ParticlesManager()
{
}


ParticlesManager::~ParticlesManager()
{
}

void ParticlesManager::render()
{
	for (Particle* particle : particles) {
 		if (particle->isActive())
			particle->render();
	}
}

Particle * ParticlesManager::getParticle(ParticleType particleName, int x, int y)
{
	for (Particle* particle : particles) {
		if (!particle->isActive() && particle->getType() == particleName) {
			particle->setActive(true);
			particle->getTransform()->position.setX(x);
			particle->getTransform()->position.setY(y);
			return particle;
		}
	}

	Particle * newParticle = nullptr;

	//Se deben añadir las demas particulas
	if (particleName == ParticleType::Blood) {
		newParticle = new Particle(ResourceManager::getInstance()->getTexture(Blood), ParticleType::Blood, x, y);
		int rnd = Random::randomInt(0, 2);
		AnimationNumber num;
		if (rnd == 0)
			num = FirstAnim;
		else if (rnd == 1) {
			num = SecondAnim;
		}
		else {
			num = ThirdAnim;
		}
		newParticle->simpleAnimation->setAnimationNumber(num);
		newParticle->simpleAnimation->setSize(25 * Game::getGame()->getScale(), 25 * Game::getGame()->getScale());
		newParticle->setActive(true);
		particles.push_back(newParticle);
	}
	else if (particleName == ParticleType::GunnerBulletExplosion) {
		newParticle = new Particle(ResourceManager::getInstance()->getTexture(GunnerBulletExplosion), ParticleType::GunnerBulletExplosion, x, y);
		int rnd = Random::randomInt(0, 1);
		AnimationNumber num;
		if (rnd == 0)
			num = FirstAnim;
		else num = SecondAnim;
		newParticle->simpleAnimation->setAnimationNumber(num);
		newParticle->simpleAnimation->setSize(14 * Game::getGame()->getScale(), 14 * Game::getGame()->getScale());
		newParticle->setActive(true);
		particles.push_back(newParticle);
	}
	return newParticle;
}

ParticlesManager * ParticlesManager::getInstance()
{
	if (instance == nullptr)
		instance = new ParticlesManager();
	return instance;
}