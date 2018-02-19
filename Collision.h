#ifndef _COLLISION_H
#define _COLLISION_H

#include "Transform.h"
#include "GameObject.h"

class Sphere
{
public:
	Sphere(float radius, Transform* transform) : _radius(radius), _transform(transform) {}
	float GetBoundingRadius() const { return _radius; }
	Transform* GetTransform() const { return _transform; }

	bool CollisionCheck(Sphere* otherSphere)
	{
		Vector centre1 = _transform->GetPosition();
		Vector centre2 = otherSphere->GetTransform()->GetPosition();

		Vector distance = centre2 - centre1;

		float sumOfBoundingRadii = _radius + otherSphere->GetBoundingRadius();

		if (distance.GetSqrMagnitude() < (sumOfBoundingRadii * sumOfBoundingRadii)) 
		{
			return true;
		}

		return false;
	}

private:
	float _radius;
	Transform* _transform;
};

struct Contact
{
	GameObject * first;
	GameObject * second;
};

namespace CollisionDetector
{
	static std::vector<Contact*> DetectCollisions(std::vector<GameObject>gameobjects) 
	{
		for (int i = 0; i < gameObjects.size() - 1; i++)
		{
			for (int j = 1 + 1; j < gameObjects.size(); j++)
			{
				gameObjects[i]->GetParticleModel()->GetBoundingSphere().CollisionCheck(gameObjects[j]->GetParticleModel()->GetGetBoundingSphere())
			}
		}
	};
}
#endif //!_COLLISION_H
