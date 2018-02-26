#include "Collision.h"	
std::vector<Contact> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{
	//TODO: Quadtree?

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

void Collision::ResolveCollision(std::vector<Contact> contacts)
{
	for (auto contact : contacts)
	{
		//Resolve Interpenertration

		Vector velocityA = contact.first->GetParticleModel()->GetVelocity();
		Vector velocityB = contact.second->GetParticleModel()->GetVelocity();

		float massA = contact.first->GetParticleModel()->GetMass();
		float massB = contact.second->GetParticleModel()->GetMass();

		//coeffiecient of restitution hard coded as 0.5
		velocityA = ((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*0.5)) / (massA + massB));
		velocityB = ((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massA*0.5)) / (massA + massB));

		contact.first->GetParticleModel()->SetVelocity(velocityA);

		contact.second->GetParticleModel()->SetVelocity(velocityB);
	}
}
