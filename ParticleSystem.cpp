#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Appearance* appearance, float mass) 
	:_appearance(appearance), _mass(mass)
{
	_isAlive = false;
	_totalTime = 0.0f;
	_spawnTime = 0.0f;
	_destroyTime = 0.0f;
	_particlePool = new GameObjectPool();
}


ParticleSystem::~ParticleSystem()
{
	for (auto particle : _particles)
		delete particle;

	_particlePool->CleanUp();
}

void ParticleSystem::AddParticle(GameObject* particle)
{
	_particles.push_back(_particlePool->GetGameObject(particle));
}

void ParticleSystem::Activate(Vector3D position, Vector3D velocity, float variance, float lifeSpan, float particlesPerSecond, float particleLife)
{
	_lifeSpan = lifeSpan;
	_particlesPerSecond = particlesPerSecond;
	_variance = variance;

	_particleLife = particleLife;
	_initialVelocity = velocity;
	_emitterLocation = position;
	_isAlive = true;
	_totalTime = 0.0f;
}

void ParticleSystem::Deactivate()
{
	_isAlive = false;
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
	_totalTime += deltaTime;

	if ((_totalTime <= _lifeSpan || _lifeSpan <= 0.0f) && _isAlive)
	{
		_spawnTime += deltaTime;

		if (_spawnTime > 1.0f / _particlesPerSecond)
		{
			Transform* transform = new Transform(_emitterLocation, { 1,0,0, 0}, { 1,1,1 });
			ParticleModel* particle = new ParticleModel(_mass, _initialVelocity+ Vector3D{ _variance * (float)rand() / (RAND_MAX)-_variance/2, _variance * (float)rand() / (RAND_MAX)-_variance / 2, _variance * (float)rand() / (RAND_MAX)-_variance / 2 }, transform);

			AddParticle(new GameObject("Particle", _appearance, transform, particle, nullptr));
			_spawnTime = 0.0f;
		}
	}
	else
	{
		_isAlive = false;
	}

	
	if (_particles.size() && _totalTime > _particleLife)
	{
		_destroyTime += deltaTime;

		if (_destroyTime >= 1.0f/_particlesPerSecond && _particles.size())
		{
			_particlePool->ReturnGameObject(_particles[0]);
			_particles.erase(_particles.begin());
			_destroyTime = 0.0f;
		}
	}

	for (auto particle : _particles)
	{
		particle->Update(deltaTime);
	}
}

bool ParticleSystem::IsAlive()
{
	return _isAlive;
}

