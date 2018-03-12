#ifndef _COLLISION_H
#define _COLLISION_H

#include"GameObject.h"
#include <vector>

struct Contact
{
	GameObject * A;
	Vector contactNormalA;
	GameObject * B;
	Vector contactNormalB;
	float penetrationDepth;
};

namespace Collision
{
	std::vector<Contact> DetectCollisions(std::vector<GameObject*>gameObjects);
	void ResolveCollision(std::vector<Contact>contacts);
};
#endif // !_COLLISION_H

