#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Appearance* appearance, float mass) 
{
	_isAlive = false;
	_totalTime = 0.0f;
	_spawnTime = 0.0f;
	_destroyTime = 0.0f;
	Transform* transform = new Transform();
	initialiser = GameObject("Particle", appearance, transform, new ParticleModel(mass, {0.0f, 0.0f, 0.0f}, transform), nullptr);
	_particlePool = new GameObjectPool(initialiser);

	_particlePool->PreloadGameObjects(10);
}


ParticleSystem::~ParticleSystem()
{
	for (auto particle : _particles)
		delete particle;

	_particlePool->CleanUp();
}

void ParticleSystem::AddParticle()
{
	_particles.push_back(_particlePool->GetGameObject());
}

void ParticleSystem::Activate(Vector3D velocity, float variance, float lifeSpan, float particlesPerSecond, float particleLife)
{
	_lifeSpan = lifeSpan;
	_particlesPerSecond = particlesPerSecond;
	_variance = variance;

	_particleLife = particleLife;
	_initialVelocity = velocity;
	
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

void ParticleSystem::Update(float deltaTime, Vector3D position)
{
	_totalTime += deltaTime;

	if ((_totalTime <= _lifeSpan || _lifeSpan <= 0.0f) && _isAlive)
	{
		_spawnTime += deltaTime;

		if (_spawnTime > 1.0f / _particlesPerSecond)
		{
			AddParticle();
			_particles.at(_particles.size()-1)->GetTransform()->SetPosition(position);
			_particles.at(_particles.size() - 1)->GetPhysicsComponent()->SetVelocity(_initialVelocity + 
				Vector3D{ _variance * (float)rand() / (RAND_MAX)-_variance / 2, 
				_variance * (float)rand() / (RAND_MAX)-_variance / 2, 
				_variance * (float)rand() / (RAND_MAX)-_variance / 2 });

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

