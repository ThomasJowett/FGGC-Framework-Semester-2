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
	GameObject(string type, Appearance * appearance, Transform * transform, ParticleModel * particleModel, Collider* collider);
	~GameObject();

	string GetType() const { return _type; }
	Transform * GetTransform() const { return _transform; }
	Appearance * GetAppearance() const { return _appearance; }
	ParticleModel* GetPhysicsComponent() const { return _particleModel; }
	Collider* GetCollider() const { return _collider; }
	
	void SetParent(GameObject * parent) { _parent = parent; }

	virtual void Update(float deltaTime);
	void Draw(ID3D11DeviceContext * pImmediateContext);

protected:
	string _type;
	
	Transform * _transform;
	Appearance * _appearance;
	ParticleModel * _particleModel;
	Collider* _collider;

private:
	GameObject * _parent;
};

