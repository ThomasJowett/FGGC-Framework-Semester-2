#ifndef _COLLISION_H
#define _COLLISION_H

#include"Transform.h"

class Sphere
{
public:
	Sphere(float radius, Transform* transform) : _radius(radius), _transform(transform) { _collided = false; }
	float GetBoundingRadius() const { return _radius; }

	void Update();

	void SetCollided(bool collided) { _collided = collided; }
	bool GetCollided() const { return _collided; }
	Transform* GetTransform() const { return _transform; }
private:
	float _radius;
	bool _collided;
	Transform* _transform;
};

class Collision {
public:
	static bool SphereSphereCollision(Sphere * sphere1, Sphere* sphere2)
	{
		Vector centre1 = sphere1->GetTransform()->GetPosition();
		Vector centre2 = sphere2->GetTransform()->GetPosition();

		Vector distance = centre2 - centre1;

		float sumOfBoundingRadii = sphere1->GetBoundingRadius() + sphere2->GetBoundingRadius();
		if (distance.GetSqrMagnitude() < (sumOfBoundingRadii * sumOfBoundingRadii)) {
			sphere1->SetCollided(true);
			sphere2->SetCollided(true);
			return true;
		}

		return false;
	}
};
#endif //!_COLLISION_H
