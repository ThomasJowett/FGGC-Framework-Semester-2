#include "Collision.h"	
std::vector<Contact> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{
	//TODO: Quadtree?

	vector<Contact>contacts;
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			float penetrationDepth = gameObjects[i]->GetParticleModel()->GetBoundingSphere()->CollisionCheck(gameObjects[j]->GetParticleModel()->GetBoundingSphere());
			if (penetrationDepth > 0.0f)
			{
				Vector contactNormalA = gameObjects[i]->GetTransform()->GetPosition() - gameObjects[j]->GetTransform()->GetPosition();
				Vector contactNormalB = gameObjects[j]->GetTransform()->GetPosition() - gameObjects[i]->GetTransform()->GetPosition();

				contactNormalA.Normalize();
				contactNormalB.Normalize();
				contacts.push_back({ gameObjects[i], contactNormalA, gameObjects[j],contactNormalB, penetrationDepth });
			}
		}
	}
	return contacts;
}

void Collision::ResolveCollision(std::vector<Contact> contacts)
{
	for (auto contact : contacts)
	{
		Vector velocityA = contact.first->GetParticleModel()->GetVelocity();
		Vector velocityB = contact.second->GetParticleModel()->GetVelocity();


		//TODO: Resolve Interpenertration
		//contact.first->GetTransform()->SetPosition(contact.first->GetTransform()->GetPosition() + (contact.contactNormalA*(contact.penetrationDepth/2)));
		//contact.second->GetTransform()->SetPosition(contact.second->GetTransform()->GetPosition() + (contact.contactNormalB*(contact.penetrationDepth/2)));

		float massA = contact.first->GetParticleModel()->GetMass();
		float massB = contact.second->GetParticleModel()->GetMass();

		//coeffiecient of restitution hard coded as 0.5
		velocityA = (((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*0.5))) / (massA + massB));
		velocityB = (((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massA*0.5))) / (massA + massB));

		contact.first->GetParticleModel()->SetVelocity(velocityA);

		contact.second->GetParticleModel()->SetVelocity(velocityB);
	}
}
