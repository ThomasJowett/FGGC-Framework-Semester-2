#pragma once

#include <directxmath.h>
#include <d3d11_1.h>
#include <string>

#include "Transform.h"
#include "Appearance.h"
#include "ParticleModel.h"
#include "Collision.h"

using namespace DirectX;
using namespace std;

class GameObject
{
public:
	GameObject(string type, Appearance* appearance, Transform * transform, ParticleModel* particlemodel, float boundingRadius);
	~GameObject();

	string GetType() const { return _type; }
	Transform * GetTransform() const { return _transform; }
	Appearance * GetAppearance() const { return _appearance; }
	ParticleModel* GetParticleModel() const { return _particleModel; }
	
	void SetParent(GameObject * parent) { _parent = parent; }

	void Update(float t);
	void Draw(ID3D11DeviceContext * pImmediateContext);

	Sphere * GetBoundingSphere()const { return _boundingSphere; }

private:
	string _type;
	
	Transform * _transform;
	Appearance* _appearance;
	ParticleModel* _particleModel;

	Sphere * _boundingSphere;

	GameObject * _parent;
};

