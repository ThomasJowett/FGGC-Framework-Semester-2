#include "ParticleSystem.h"



ParticleSystem::ParticleSystem()
{
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Update(float deltaTime)
{
	for (auto particle : _particles)
	{
		particle->Update(deltaTime);
	}
}

void ParticleSystem::Draw()
{
}
