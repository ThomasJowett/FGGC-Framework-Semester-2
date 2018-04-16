#include "GameObject.h"

GameObject::GameObject()
	:_type("NULL"), _appearance(nullptr), _transform(new Transform()), _physicsComponent(nullptr), _collider(nullptr)
{
	_parent = nullptr;
}

GameObject::GameObject(string type, Appearance* appearance, Transform * transform, ParticleModel* particlemodel, Collider* collider)
	: _type(type), _appearance(appearance), _transform(transform), _physicsComponent(particlemodel), _collider(collider)
{
	_parent = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{	
	if (_physicsComponent != nullptr)
		_physicsComponent->Update(deltaTime);

	_transform->UpdateWorldMatrix();

	if (_parent != nullptr)
	{
		XMStoreFloat4x4(&_transform->GetWorldMatrix4x4(), this->_transform->GetWorldMatrix() * _parent->_transform->GetWorldMatrix());
	}
}

void GameObject::Draw(ID3D11DeviceContext * pImmediateContext)
{
	_appearance->Draw(pImmediateContext);
}
