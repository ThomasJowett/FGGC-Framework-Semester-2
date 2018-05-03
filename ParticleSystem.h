#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H

#include <vector>
#include "GameObject.h"
#include "ObjectPool.h"

class ParticleSystem
{
public:
	ParticleSystem(Appearance* appearance, float mass);
	~ParticleSystem();

	void AddParticle();
	void Activate(Vector3D velocity, float variance, float lifeSpan, float particlesPerSecond, float particleLife);
	void Deactivate();

	void Render(ID3D11DeviceContext * pImmediateContext);
	void Update(float deltaTime, Vector3D position);
	bool IsAlive();

	int GetCurrentParticleCount() const { return _particles.size(); }

	vector<GameObject*> GetParticles() const { return _particles; }

	void SetLifeSpan(const float lifeSpan) { _lifeSpan = lifeSpan; }
	float GetLifeSpan()const { return _lifeSpan; }

private:
	std::vector<GameObject*> _particles;
	GameObject initialiser;
	GameObjectPool* _particlePool;
	float _lifeSpan;
	float _totalTime;
	float _spawnTime;
	float _destroyTime;
	float _particleLife;
	
	float _particlesPerSecond;
	float _variance;
	
	bool _isAlive;

	Vector3D _initialVelocity;
	

	
};
#endif // !_PARTICLESYSTEM_H
