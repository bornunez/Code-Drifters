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

void ParticlesManager::randomizeParticle(Particle * p, int animations)
{
	Uint32 rndAnim = Random::randomInt(0, animations-1);
	Uint32 rndAngle = Random::randomInt(0, 359);
	p->simpleAnimation->setAngle(rndAngle);
	p->simpleAnimation->setAnimationNumber(rndAnim);
}

Particle * ParticlesManager::getParticle(ParticleType particleName, int x, int y)
{
	for (Particle* particle : particles) {
		if (!particle->isActive() && particle->getType() == particleName) {
			particle->setActive(true);
			particle->getTransform()->position.setX(x);
			particle->getTransform()->position.setY(y);
			if(particleName == ParticleType::Blood){
				randomizeParticle(particle, 3);
			}
			else if (particleName == ParticleType::GunnerBulletExplosion) {
				randomizeParticle(particle, 2);
			}
			return particle;
		}
	}

	Particle * newParticle = nullptr;

	//Se deben añadir las demas particulas
	if (particleName == ParticleType::Blood) {
		newParticle = new Particle(ResourceManager::getInstance()->getTexture(Blood), ParticleType::Blood, x, y);
		randomizeParticle(newParticle, 3);
		newParticle->simpleAnimation->setSize(25 * Game::getGame()->getScale(), 25 * Game::getGame()->getScale());
		newParticle->setActive(true);
		particles.push_back(newParticle);
	}
	else if (particleName == ParticleType::GunnerBulletExplosion) {
		newParticle = new Particle(ResourceManager::getInstance()->getTexture(GunnerBulletExplosion), ParticleType::GunnerBulletExplosion, x, y);
		randomizeParticle(newParticle, 2);
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