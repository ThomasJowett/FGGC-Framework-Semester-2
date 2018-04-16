#include "Collision.h"	
std::vector<Contact> Collision::DetectCollisions(std::vector<GameObject*> gameObjects)
{

	QuadTree* quadTree = new QuadTree( new AABB(new Transform(), 30.0f, 100.0f,30.0f), 0);
	quadTree->Clear();

	for (auto gameObject : gameObjects)
	{
		if(gameObject->GetCollider())
			quadTree->Insert(gameObject);
	}
	vector<Contact>contacts;

	for (auto gameObject : gameObjects)
	{	
		
		if (gameObject->GetCollider())
		{
			std::vector<GameObject*>coarseList = quadTree->Retrieve(gameObject);
			
			if (coarseList.size())
			{
				
				for (auto otherObject : coarseList)
				{
					if (otherObject != gameObject)
					{
						Vector3D contactNormal;
						float penetrationDepth;

						if (gameObject->GetCollider()->IntersectsCollider(otherObject->GetCollider(), contactNormal, penetrationDepth))
						{
							contacts.push_back({ gameObject, otherObject,contactNormal, penetrationDepth });
						}
					}
				}
			}
		}
		ResolveCollision(contacts);
		contacts.clear();
	}
	/*
	for (int i = 0; i < gameObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < gameObjects.size(); j++)
		{
			if (gameObjects[i]->GetCollider() != nullptr && gameObjects[j]->GetCollider() != nullptr)
			{
				Vector3D contactNormal;
				float penetrationDepth;

				if (gameObjects[i]->GetCollider()->IntersectsCollider(gameObjects[j]->GetCollider(), contactNormal, penetrationDepth))
				{
					contacts.push_back({ gameObjects[i], gameObjects[j],contactNormal, penetrationDepth });
				}
			}
		}
	}*/
	delete quadTree;
	return contacts;
}

void Collision::ResolveCollision(std::vector<Contact> contacts)
{
	for (auto contact : contacts)
	{
		Vector3D velocityA;
		Vector3D velocityB;
		float massA = 0.0f, restitutionA;
		float massB = 0.0f, restitutionB;

		bool moveA, moveB;

		if (contact.A->GetPhysicsComponent() != nullptr)
		{
			velocityA = contact.A->GetPhysicsComponent()->GetVelocity();
			massA = contact.A->GetPhysicsComponent()->GetMass();
			moveA = true;
			restitutionA = contact.A->GetPhysicsComponent()->GetPhysicsMaterial().elasticity;
		}
		else
			moveA = false;

		if (contact.B->GetPhysicsComponent() != nullptr)
		{
			velocityB = contact.B->GetPhysicsComponent()->GetVelocity();
			massB = contact.B->GetPhysicsComponent()->GetMass();
			moveB = true;
			restitutionB = contact.B->GetPhysicsComponent()->GetPhysicsMaterial().elasticity;
		}
		else
			moveB = false;

		if (!moveA && !moveB)
		{
			//do nothing
		}
		else if (moveA && moveB)
		{
			float coeffiecientOfRestitution = (restitutionA + restitutionB) / 2;
			//Resolve Interpenertration
			contact.A->GetTransform()->SetPosition(contact.A->GetTransform()->GetPosition() + ((contact.contactNormal*(contact.penetrationDepth)) * (massB / massA + massB)));
			contact.B->GetTransform()->SetPosition(contact.B->GetTransform()->GetPosition() + ((contact.contactNormal*-(contact.penetrationDepth)) * (massA / massA + massB)));

			//add impulse
			contact.A->GetPhysicsComponent()->SetVelocity((((velocityA*massA) + (velocityB*massB) + ((velocityB - velocityA)*(massB*coeffiecientOfRestitution))) / (massA + massB)));
			contact.B->GetPhysicsComponent()->SetVelocity((((velocityA*massA) + (velocityB*massB) + ((velocityA - velocityB)*(massA*coeffiecientOfRestitution))) / (massA + massB)));
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
