#ifndef _COLLISION_H
#define _COLLISION_H

#include"GameObject.h"
#include <vector>

struct Contact
{
	GameObject * first;
	GameObject * second;
};

namespace Collision
{
	std::vector<Contact> DetectCollisions(std::vector<GameObject*>gameObjects);
	void ResolveCollision(std::vector<Contact>contacts);
};
#endif // !_COLLISION_H

