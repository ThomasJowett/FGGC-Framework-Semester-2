#ifndef _COLLISION_H
#define _COLLISION_H

#include"GameObject.h"
#include <vector>

struct Contact
{
	GameObject * first;
	GameObject * second;
};

class Collision
{
public:
	static std::vector<Contact> DetectCollisions(std::vector<GameObject*>gameObjects)
	{
		//Quadtree?

		vector<Contact>contacts;
		for (int i = 0; i < gameObjects.size() - 1; i++)
		{
			for (int j = 1 + 1; j < gameObjects.size(); j++)
			{
				if (gameObjects[i]->GetParticleModel()->GetBoundingSphere()->CollisionCheck(gameObjects[j]->GetParticleModel()->GetBoundingSphere()))
				{
					contacts.push_back({ gameObjects[i], gameObjects[j] });
				}
			}
		}
		return contacts;
	}
};
#endif // !_COLLISION_H

