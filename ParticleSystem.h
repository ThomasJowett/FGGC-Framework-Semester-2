#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H

#include <vector>
#include "GameObject.h"

class ParticleSystem
{
public:
	ParticleSystem(float lifeSpan, int particlesPerSecond, Appearance* appearance, float mass, float radius);
	~ParticleSystem();

	void AddParticle(GameObject* particle);
	void Activate(Vector position, Vector velocity, bool randomise);

	void Render(ID3D11DeviceContext * pImmediateContext);
	void Update(float deltaTime);
	bool IsAlive();

private:
	std::vector<GameObject*> _particles;
	float _lifeSpan;
	float _totalTime;
	float _oldTime;

	int _currentParticleCount;
	
	float _particlesPerSecond;
	
	bool _isAlive;

	Vector _emitterLocation;

	Vector _initialVelocity;

	Appearance* _appearance;

	float _mass;
	float _radius;
};
#endif // !_PARTICLESYSTEM_H
