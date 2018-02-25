#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(float lifeSpan) : _lifeSpan(lifeSpan)
{
	_isAlive = false;
	_totalTime = 0.0f;
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::AddParticle(GameObject* particle)
{
	_particles.push_back(particle);
}

void ParticleSystem::Activate(Vector position, Vector velocity, bool randomise)
{
	for (auto particle : _particles)
	{
		particle->GetTransform()->SetPosition(position);
		if (randomise)
			particle->GetParticleModel()->SetVelocity(velocity + Vector{ 1.0f * (float)rand() / (RAND_MAX)-0.5f, 1.0f * (float)rand() / (RAND_MAX)-0.5f, 1.0f * (float)rand() / (RAND_MAX)-0.5f });
		else
			particle->GetParticleModel()->SetVelocity(velocity);
	}

	_isAlive = true;
}

void ParticleSystem::Render(ID3D11DeviceContext * pImmediateContext)
{
	for (auto particle : _particles)
	{
		particle->Draw(pImmediateContext);
	}
}

void ParticleSystem::Update(float deltaTime)
{
	float quat = _lifeSpan / 0.016f;
	float decrement = 1.0f / quat;

	if (_totalTime <= _lifeSpan && _isAlive)
	{
		_totalTime += deltaTime;

		for (auto particle : _particles)
		{
			particle->Update(deltaTime);
		}
	}
	else
	{
		_totalTime = 0.0f;
		_isAlive = false;
	}
}

bool ParticleSystem::IsAlive()
{
	return false;
}

