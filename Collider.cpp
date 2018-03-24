#include "Collider.h"

bool AABB::CollisionCheck(Collider * otherCollider, Vector3D & normal, float & penetrationDepth)
{
		if (Sphere* otherSphere = dynamic_cast<Sphere*>(otherCollider))
		{
			Vector3D seperationVector = otherSphere->GetCentre() - GetCentre();

			Vector3D closestPoint;

			if (seperationVector.x < GetXMin())
				closestPoint.x = GetXMin();
			else if (seperationVector.x > GetXMax())
				closestPoint.x = GetXMax();
			else
				closestPoint.x = seperationVector.x;

			if (seperationVector.y < GetYMin())
				closestPoint.y = GetYMin();
			else if (seperationVector.y > GetYMax())
				closestPoint.y = GetYMax();
			else
				closestPoint.y = seperationVector.y;

			if (seperationVector.z < GetZMin())
				closestPoint.z = GetZMin();
			else if (seperationVector.z > GetZMax())
				closestPoint.z = GetZMax();
			else
				closestPoint.z = seperationVector.z;

			Vector3D distance = otherSphere->GetCentre() - closestPoint;

			if (distance.GetSqrMagnitude() < (otherSphere->GetBoundingRadius() * otherSphere->GetBoundingRadius()))
			{

				penetrationDepth = otherSphere->GetBoundingRadius() - distance.GetMagnitude();
				normal = (GetCentre() - closestPoint).GetNormalized() * -1.0f;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
			return false;
}

bool Sphere::CollisionCheck(Collider * otherCollider, Vector3D & normal, float & penetrationDepth)
{
	if (Sphere* otherSphere = dynamic_cast<Sphere*>(otherCollider))
	{
		Vector3D seperationVector = GetCentre() - otherSphere->GetCentre();

		float sumOfBoundingRadii = _radius + otherSphere->GetBoundingRadius();

		if ((sumOfBoundingRadii*sumOfBoundingRadii) > seperationVector.GetSqrMagnitude())
		{
			penetrationDepth = sumOfBoundingRadii - seperationVector.GetMagnitude();
			normal = seperationVector.GetNormalized();
			return true;
		}
		else
			return false;

	}
	//Sphere on Box

	else if (AABB* otherBox = dynamic_cast<AABB*>(otherCollider))
	{
		Vector3D seperationVector = GetCentre() - otherBox->GetCentre();

		Vector3D closestPoint;

		if (seperationVector.x < otherBox->GetXMin())
			closestPoint.x = otherBox->GetXMin();
		else if (seperationVector.x > otherBox->GetXMax())
			closestPoint.x = otherBox->GetXMax();
		else
			closestPoint.x = seperationVector.x;

		if (seperationVector.y < otherBox->GetYMin())
			closestPoint.y = otherBox->GetYMin();
		else if (seperationVector.y > otherBox->GetYMax())
			closestPoint.y = otherBox->GetYMax();
		else
			closestPoint.y = seperationVector.y;

		if (seperationVector.z < otherBox->GetZMin())
			closestPoint.z = otherBox->GetZMin();
		else if (seperationVector.z > otherBox->GetZMax())
			closestPoint.z = otherBox->GetZMax();
		else
			closestPoint.z = seperationVector.z;


		Vector3D distance = seperationVector - closestPoint;

		if (distance.GetSqrMagnitude() < _radius*_radius)
		{

			penetrationDepth = _radius - distance.GetMagnitude();
			normal = (GetCentre() - closestPoint).GetNormalized();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
