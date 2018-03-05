#ifndef _COLLISION_H
#define _COLLISION_H

#include"GameObject.h"
#include <vector>

struct Contact
{
	GameObject * first;
	Vector contactNormalA;
	GameObject * second;
	Vector contactNormalB;
	float penetrationDepth;
};

namespace Collision
{
	std::vector<Contact> DetectCollisions(std::vector<GameObject*>gameObjects);
	void ResolveCollision(std::vector<Contact>contacts);
};
#endif // !_COLLISION_H

