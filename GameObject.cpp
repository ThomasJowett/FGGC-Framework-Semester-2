#include "GameObject.h"

GameObject::GameObject(string type, Appearance* appearance, Transform * transform, ParticleModel* particlemodel) : _type(type), _appearance(appearance), _transform(transform), _particleModel(particlemodel)
{
	_parent = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime)
{	
	if (_particleModel != nullptr)
		_particleModel->Update(deltaTime);

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
