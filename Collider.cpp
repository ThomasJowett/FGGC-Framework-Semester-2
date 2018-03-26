#include "Collider.h"

bool AABB::CollisionCheck(Collider * otherCollider, Vector3D & normal, float & penetrationDepth)
{
	//box on sphere
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
				normal = ((otherSphere->GetCentre() - closestPoint) / distance.GetMagnitude()).GetNormalized();
				return true;
			}
			else
			{
				return false;
			}
		}

		//Box on Box
		else if (AABB* otherBox = dynamic_cast<AABB*>(otherCollider))
		{
			if (GetXMax() < otherBox->GetXMin()
				|| GetXMin() > otherBox->GetXMax()
				|| GetYMax() < otherBox->GetYMin()
				|| GetYMin() > otherBox->GetYMax()
				|| GetZMax() < otherBox->GetZMin()
				|| GetZMin() > otherBox->GetZMax())
			{
				return false;
			}
			else
			{
				float mtvDistance = FLT_MAX;
				Vector3D mtvAxis;

				//X Axis
				if (!TestAxis({ 1.0f, 0.0f, 0.0f }, GetXMin(), GetXMax(), otherBox->GetXMin(), otherBox->GetXMax(), mtvAxis, mtvDistance))
					return false;
				if (!TestAxis({ 0.0f, 1.0f, 0.0f }, GetYMin(), GetYMax(), otherBox->GetYMin(), otherBox->GetYMax(), mtvAxis, mtvDistance))
					return false;
				if (!TestAxis({ 0.0f, 0.0f, 1.0f }, GetZMin(), GetZMax(), otherBox->GetZMin(), otherBox->GetZMax(), mtvAxis, mtvDistance))
					return false;

				normal = mtvAxis.GetNormalized() *-1.0f;
				penetrationDepth = sqrt(mtvDistance);
				return true;
			}
		}
		else
			return false;
}

bool Sphere::CollisionCheck(Collider * otherCollider, Vector3D & normal, float & penetrationDepth)
{
	//Sphere on Box
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
		float temp = otherBox->GetZMin();
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


		Vector3D distance = GetCentre() - closestPoint;

		if (distance.GetSqrMagnitude() < _radius*_radius)
		{
			penetrationDepth = _radius - distance.GetMagnitude();
			normal = ((GetCentre() - closestPoint)/ distance.GetMagnitude()).GetNormalized() * -1.0f;
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

bool Collider::TestAxis(Vector3D axis, float minA, float maxA, float minB, float maxB, Vector3D & mtvAxis, float & mtvDistance)
{
	if (axis.GetSqrMagnitude() < 1.0e-8f)
		return true;

	float d0 = (maxB - minA);
	float d1 = (maxA - minB);

	if (d0 <= 0.0f || d1 <= 0.0f)
		return false;

	float overlap = (d0 < d1) ? d0 : -d1;

	Vector3D seperation = axis * (overlap / axis.GetSqrMagnitude());

	if (seperation.GetSqrMagnitude() < mtvDistance)
	{
		mtvDistance = seperation.GetSqrMagnitude();
		mtvAxis = seperation;
	}
	return true;
}
