#ifndef _COLLIDER_H
#define _COLLIDER_H

#include "Transform.h"

class Collider
{
public:
	Collider(Transform* transform) :_transform(transform) {}
	~Collider() {}

	virtual bool CollisionCheck(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) = 0;

	void SetTransform(Transform* transform) { _transform = transform; }
	Transform* GetTransform() const { return _transform; }

	bool TestAxis(Vector3D axis, float minA, float maxA, float minB, float maxB, Vector3D& mtvAxis, float& mtvDistance);

protected:
	Transform* _transform;
};

class AABB : public Collider
{
public:
	AABB(Transform* transform, float height, float width, float depth)
		:Collider(transform), _height(height), _width(width), _depth(depth) {}

	bool CollisionCheck(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) override;


	float GetXMin() const { return _transform->GetPosition().x - (_width / 2); }
	float GetXMax() const { return _transform->GetPosition().x + (_width / 2); }
	float GetYMin() const { return _transform->GetPosition().y - (_height / 2); }
	float GetYMax() const { return _transform->GetPosition().y + (_height / 2); }
	float GetZMin() const { return _transform->GetPosition().z - (_depth / 2); }
	float GetZMax() const { return _transform->GetPosition().z + (_depth / 2); }
	Vector3D GetCentre() const { return _transform->GetPosition(); }

private:
	float _height, _width, _depth;
};

class Sphere : public Collider
{
public:
	Sphere(float radius, Transform* transform) : _radius(radius), Collider(transform) {}
	~Sphere() {}

	bool CollisionCheck(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) override;

	float GetBoundingRadius() const { return _radius; }
	Vector3D GetCentre() const { return _transform->GetPosition(); }
	
private:
	float _radius;
};


#endif //!_COLLIDER_H
