#ifndef _COLLIDER_H
#define _COLLIDER_H

#include "Transform.h"

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
#endif //!_COLLIDER_H
