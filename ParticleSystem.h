#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H

#include <vector>
#include "GameObject.h"
#include "ObjectPool.h"

class ParticleSystem
{
public:
	ParticleSystem(Appearance* appearance, float mass, float radius);
	~ParticleSystem();

	void AddParticle(GameObject* particle);
	void Activate(Vector position, Vector velocity, float variance, float lifeSpan, float particlesPerSecond);
	void Deactivate();

	void Render(ID3D11DeviceContext * pImmediateContext);
	void Update(float deltaTime);
	bool IsAlive();

	int GetCurrentParticleCount() const { return _particles.size(); }

	vector<GameObject*> GetParticles() const { return _particles; }

	void SetAppearance(Appearance* appearance) { _appearance = appearance;}

	void SetLifeSpan(const float lifeSpan) { _lifeSpan = lifeSpan; }
	float GetLifeSpan()const { return _lifeSpan; }

private:
	std::vector<GameObject*> _particles;
	GameObjectPool* _particlePool;
	float _lifeSpan;
	float _totalTime;
	float _spawnTime;
	float _destroyTime;
	float _particleLife;
	
	float _particlesPerSecond;
	float _variance;
	
	bool _isAlive;

	Vector _emitterLocation;

	Vector _initialVelocity;

	Appearance* _appearance;

	float _mass;
	float _radius;

	
};
#endif // !_PARTICLESYSTEM_H
