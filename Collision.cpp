#include "Collision.h"	
std::vector<Contact> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{
	//TODO: Quadtree?

	vector<Contact>contacts;
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			if (gameObjects[i]->GetCollider() != nullptr && gameObjects[j]->GetCollider() != nullptr)
			{
				Vector3D contactNormal;
				float penetrationDepth;
				
				if(gameObjects[i]->GetCollider()->CollisionCheck(gameObjects[j]->GetCollider(), contactNormal, penetrationDepth))
				{
					contacts.push_back({ gameObjects[i], gameObjects[j],contactNormal, penetrationDepth });
				}
			}
		}
	}
	return contacts;
}

void Collision::ResolveCollision(std::vector<Contact> contacts)
{
	for (auto contact : contacts)
	{
		Vector3D velocityA;
		Vector3D velocityB;
		float massA = 0.0f;
		float massB = 0.0f;

		bool moveA, moveB;

		if (contact.A->GetPhysicsComponent() != nullptr)
		{
			velocityA = contact.A->GetPhysicsComponent()->GetVelocity();
			massA = contact.A->GetPhysicsComponent()->GetMass();
			moveA = true;
		}
		else
			moveA = false;

		if (contact.B->GetPhysicsComponent() != nullptr)
		{
			velocityB = contact.B->GetPhysicsComponent()->GetVelocity();
			massB = contact.B->GetPhysicsComponent()->GetMass();
			moveB = true;
		}
		else
			moveB = false;

		if (!moveA && !moveB)
		{
			//do nothing
		}
		else if (moveA && moveB)
		{
			//Resolve Interpenertration
			contact.A->GetTransform()->SetPosition(contact.A->GetTransform()->GetPosition() + ((contact.contactNormal*(contact.penetrationDepth)) * (massB / massA + massB)));
			contact.B->GetTransform()->SetPosition(contact.B->GetTransform()->GetPosition() + ((contact.contactNormal*-(contact.penetrationDepth)) * (massA / massA + massB)));

			//coeffiecient of restitution hard coded as 0.5
			contact.A->GetPhysicsComponent()->SetVelocity((((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*0.5))) / (massA + massB)));
			contact.B->GetPhysicsComponent()->SetVelocity((((velocityA*massA) + (velocityB*massB) + ((velocityA - velocityB)*(massA*0.5))) / (massA + massB)));
		}
		else if (moveA && !moveB)
		{
			//move only A
			contact.A->GetTransform()->SetPosition(contact.A->GetTransform()->GetPosition() + (contact.contactNormal*contact.penetrationDepth));

			contact.A->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(contact.A->GetPhysicsComponent()->GetVelocity(), contact.contactNormal)* 0.8);
		}
		else if (!moveA && moveB)
		{
			//move only B
			contact.B->GetTransform()->SetPosition(contact.B->GetTransform()->GetPosition() + (contact.contactNormal*contact.penetrationDepth));

			contact.B->GetPhysicsComponent()->SetVelocity(Vector3D::Reflect(contact.B->GetPhysicsComponent()->GetVelocity(), contact.contactNormal)* 0.8);
		}
	}
}
