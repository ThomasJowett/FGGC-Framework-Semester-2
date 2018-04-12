#ifndef _COLLISION_H
#define _COLLISION_H

#include"GameObject.h"
#include "QuadTree.h"
#include <vector>

struct Contact
{
	GameObject * A;
	GameObject * B;
	Vector3D contactNormal;
	float penetrationDepth;
};

namespace Collision
{
	std::vector<Contact> DetectCollisions(std::vector<GameObject*>gameObjects);
	void ResolveCollision(std::vector<Contact>contacts);
};
#endif // !_COLLISION_H

