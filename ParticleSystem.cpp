#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(float lifeSpan, int particlesPerSecond, Appearance* appearance, float mass, float radius) : _lifeSpan(lifeSpan), _particlesPerSecond(particlesPerSecond), _appearance(appearance), _mass(mass), _radius(radius)
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
	/*
	for (auto particle : _particles)
	{
		particle->GetTransform()->SetPosition(position);
		if (randomise)
			particle->GetParticleModel()->SetVelocity(velocity + Vector{ 1.0f * (float)rand() / (RAND_MAX)-0.5f, 1.0f * (float)rand() / (RAND_MAX)-0.5f, 1.0f * (float)rand() / (RAND_MAX)-0.5f });
		else
			particle->GetParticleModel()->SetVelocity(velocity);
	}*/
	_initialVelocity = velocity;
	_emitterLocation = position;
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
		if (_oldTime + deltaTime > 1 / _particlesPerSecond)
		{
			Transform* transform = new Transform(_emitterLocation, { 1,0,0, }, { 1,1,1 });
			ParticleModel* particle = new ParticleModel(_mass, _initialVelocity, _radius, transform);

			AddParticle(new GameObject("Particle", _appearance, transform, particle));
		}

		if (_lifeSpan > 0.0f)
		{
			_totalTime += deltaTime;
		}
		else
		{
			_totalTime = _lifeSpan;
		}

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

