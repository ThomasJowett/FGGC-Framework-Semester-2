#ifndef _COLLIDER_H
#define _COLLIDER_H

#include "Transform.h"

class Collider
{
public:
	Collider(Transform* transform) :_transform(transform) {}
	~Collider() {}

	virtual bool IntersectsCollider(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) const = 0;

	virtual bool ContainsPoint(Vector3D point) const = 0;

	void SetTransform(Transform* transform) { _transform = transform; }
	Transform* GetTransform() const { return _transform; }

	bool TestAxis(Vector3D axis, float minA, float maxA, float minB, float maxB, Vector3D& mtvAxis, float& mtvDistance) const;

	virtual bool TestXAxisValue(float value, bool greater)const = 0;
	virtual bool TestYAxisValue(float value, bool greater)const = 0;
	virtual bool TestZAxisValue(float value, bool greater)const = 0;

protected:
	Transform* _transform;
};

class AABB : public Collider
{
public:
	AABB(Transform* transform,  float width, float height, float depth)
		:Collider(transform),  _width(width), _height(height), _depth(depth) {}

	bool IntersectsCollider(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) const override;

	bool ContainsPoint(Vector3D point) const override;

	float GetXMin() const { return _transform->GetPosition().x - (_width / 2); }
	float GetXMax() const { return _transform->GetPosition().x + (_width / 2); }
	float GetYMin() const { return _transform->GetPosition().y - (_height / 2); }
	float GetYMax() const { return _transform->GetPosition().y + (_height / 2); }
	float GetZMin() const { return _transform->GetPosition().z - (_depth / 2); }
	float GetZMax() const { return _transform->GetPosition().z + (_depth / 2); }
	Vector3D GetCentre() const { return _transform->GetPosition(); }

	float GetHeight()const { return _height; }
	float GetWidth()const { return _width; }
	float GetDepth()const { return _depth; }

	bool TestXAxisValue(float value, bool greater) const override;
	bool TestYAxisValue(float value, bool greater) const override;
	bool TestZAxisValue(float value, bool greater) const override;

private:
	float _height, _width, _depth;
};

class Sphere : public Collider
{
public:
	Sphere(float radius, Transform* transform) : _radius(radius), Collider(transform) {}
	~Sphere() {}

	bool IntersectsCollider(Collider* otherCollider, Vector3D& normal, float& penetrationDepth) const override;

	bool ContainsPoint(Vector3D point) const override;

	float GetBoundingRadius() const { return _radius; }
	Vector3D GetCentre() const { return _transform->GetPosition(); }

	bool TestXAxisValue(float value, bool greater) const override;
	bool TestYAxisValue(float value, bool greater) const override;
	bool TestZAxisValue(float value, bool greater) const override;
	
private:
	float _radius;
};


#endif //!_COLLIDER_H
