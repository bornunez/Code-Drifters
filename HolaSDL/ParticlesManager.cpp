#include "ParticlesManager.h"
#include "ResourceManager.h"


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