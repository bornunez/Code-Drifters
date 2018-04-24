#pragma once
#include <vector>
#include "Particle.h"


class ParticlesManager 
{
private:
	//singleton
	static ParticlesManager * instance;
	ParticlesManager();

	std::vector<Particle*> particles;

public:
	static  ParticlesManager * getInstance();
	~ParticlesManager();

	void render();
	void randomizeParticle(Particle* p, int animations);
	//Crea en X,Y  una particula del tipo argumento.
	Particle * getParticle(ParticleType particleName, int x, int y);
};

