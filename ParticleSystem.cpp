#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Appearance* appearance, float mass, float radius) 
	:_appearance(appearance), _mass(mass), _radius(radius)
{
	_isAlive = false;
	_totalTime = 0.0f;
	_spawnTime = 0.0f;
	_destroyTime = 0.0f;
	_particlePool = new GameObjectPool();
}


ParticleSystem::~ParticleSystem()
{
	_particlePool->CleanUp();
}

void ParticleSystem::AddParticle(GameObject* particle)
{
	_particles.push_back(_particlePool->GetGameObject(particle));
}

void ParticleSystem::Activate(Vector position, Vector velocity, float variance, float lifeSpan, float particlesPerSecond, float particleLife)
{
	_lifeSpan = lifeSpan*1000.0f;
	_particlesPerSecond = particlesPerSecond;
	_variance = variance;

	_destroyRate = (particleLife*1000.0f) / particlesPerSecond;
	_initialVelocity = velocity;
	_emitterLocation = position;
	_isAlive = true;
}

void ParticleSystem::Deactivate()
{
	//_particlePool->CleanUp();
	_totalTime = 0.0f;
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
	if ((_totalTime <= _lifeSpan || _lifeSpan <= 0.0f) && _isAlive)
	{
		if (_spawnTime + deltaTime > 1000.0f / _particlesPerSecond)
		{
			Transform* transform = new Transform(_emitterLocation, { 1,0,0, }, { 1,1,1 });
			ParticleModel* particle = new ParticleModel(_mass, _initialVelocity+ Vector{ _variance * (float)rand() / (RAND_MAX)-_variance/2, _variance * (float)rand() / (RAND_MAX)-_variance / 2, _variance * (float)rand() / (RAND_MAX)-_variance / 2 }, _radius, transform);

			AddParticle(new GameObject("Particle", _appearance, transform, particle));
			_spawnTime = 0.0f;
		}

		_spawnTime += deltaTime;
		_totalTime += deltaTime;
	}
	else
	{
		_totalTime = 0.0f;
		_isAlive = false;
	}

	
	if (_destroyTime > _destroyRate && _particles.size())
	{
		_particlePool->ReturnGameObject(_particles[0]);
		_particles.erase(_particles.begin());
		_destroyTime = 0.0f;
	}
	else
	{
		_destroyTime += deltaTime;
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

