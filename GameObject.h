#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Transform.h"
#include "Appearance.h"
#include "ParticleModel.h"
#include "RigidBody.h"
#include "Collider.h"

using namespace DirectX;
using namespace std;

class GameObject
{
public:
	GameObject();
	GameObject(string type, Appearance * appearance, Transform * transform, ParticleModel * particleModel, Collider* collider);
	~GameObject();

	string GetType() const { return _type; }
	Transform * GetTransform() const { return _transform; }
	Appearance * GetAppearance() const { return _appearance; }
	ParticleModel* GetPhysicsComponent() const { return _physicsComponent; }
	Collider* GetCollider() const { return _collider; }
	
	void SetParent(GameObject * parent) { _parent = parent; }
	void SetTransform(Transform* transform) { _transform = transform; }
	void SetPhysicsComponent(ParticleModel* physicsComponent) { _physicsComponent = physicsComponent; }
	void SetAppearance(Appearance* appearance) { _appearance = appearance; }

	virtual void Update(float deltaTime);
	void Draw(ID3D11DeviceContext * pImmediateContext);

protected:
	string _type;
	
	Transform * _transform;
	Appearance * _appearance;
	ParticleModel * _physicsComponent;
	Collider* _collider;

private:
	GameObject * _parent;
};

