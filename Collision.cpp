#include "Collision.h"	
std::vector<Contact> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{
	//TODO: Quadtree?

	vector<Contact>contacts;
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			float penetrationDepth = gameObjects[i]->GetPhysicsComponent()->GetBoundingSphere()->CollisionCheck(gameObjects[j]->GetPhysicsComponent()->GetBoundingSphere());
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
		Vector velocityA = contact.A->GetPhysicsComponent()->GetVelocity();
		Vector velocityB = contact.B->GetPhysicsComponent()->GetVelocity();

		float massA = contact.A->GetPhysicsComponent()->GetMass();
		float massB = contact.B->GetPhysicsComponent()->GetMass();

		//Resolve Interpenertration
		contact.A->GetTransform()->SetPosition(contact.A->GetTransform()->GetPosition() + ((contact.contactNormalA*(contact.penetrationDepth)) * (massB / massA + massB)));
		contact.B->GetTransform()->SetPosition(contact.B->GetTransform()->GetPosition() + ((contact.contactNormalB*(contact.penetrationDepth)) * (massA / massA + massB)));

		//coeffiecient of restitution hard coded as 0.5
		contact.A->GetPhysicsComponent()->SetVelocity((((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*0.5))) / (massA + massB)));
		contact.B->GetPhysicsComponent()->SetVelocity((((velocityA*massA) + (velocityB*massB) + ((velocityA - velocityB)*(massA*0.5))) / (massA + massB)));
	}
}
