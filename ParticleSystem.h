#ifndef _PARTICLESYSTEM_H
#define _PARTICLESYSTEM_H

#include <vector>
#include "ParticleModel.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	void Update(float deltaTime);
	void Draw();

private:
	int _numberOfParticles;
	std::vector<ParticleModel*> _particles;

};
#endif // !_PARTICLESYSTEM_H
