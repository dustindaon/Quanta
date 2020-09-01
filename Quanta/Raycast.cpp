#include "Raycast.h"

vector<shared_ptr<GameObject>> Physics::Raycast::CastRay(Vertex ray, float length)
{
	vector<shared_ptr<GameObject>> worldObjects = Engine::Instance()->GetGameObjects();

	return Physics::Raycast::CastRay(ray, length, worldObjects);
}

vector<shared_ptr<GameObject>> Physics::Raycast::CastRay(Vertex ray, float length, vector<shared_ptr<GameObject>> targets)
{
	vector<shared_ptr<GameObject>> collidedObjects;

	// Check if raycast intersects with each object
	for (shared_ptr<GameObject> object : targets)
	{
		vector<glm::vec3> points = object->GetModel().m_outerPoints;

		// Calculate the minimum distance we'd have to multiply our ray by to reach the outer points
		// of the square.
		// Note: Negative value means that the ray is firing in the wrong direction
		float xMinRayLength = (points[0].x - ray.Position.x) / ray.Normal.x;
		float xMaxRayLength = (points[1].x - ray.Position.x) / ray.Normal.x;
		float yMinRayLength = (points[0].y - ray.Position.y) / ray.Normal.y;
		float yMaxRayLength = (points[1].y - ray.Position.y) / ray.Normal.y;
		float zMinRayLength = (points[0].z - ray.Position.z) / ray.Normal.z;
		float zMaxRayLength = (points[1].z - ray.Position.z) / ray.Normal.z;

		// Fire rays by all these scalars and see if one hits our AABB
		if (xMinRayLength > 0)
		{
			glm::vec3 xMinRayPos = ray.Position + (xMinRayLength * ray.Normal);
			if (DoesRayHit(xMinRayPos, points))
			{
				collidedObjects.push_back(object);
				continue;
			}
		}
		if (xMaxRayLength > 0)
		{
			glm::vec3 xMaxRayPos = ray.Position + (xMaxRayLength * ray.Normal);
			if (DoesRayHit(xMaxRayPos, points))
			{
				collidedObjects.push_back(object);
				continue;
			}
		}
		if (yMinRayLength > 0)
		{
			glm::vec3 yMinRayPos = ray.Position + (yMinRayLength * ray.Normal);
			if (DoesRayHit(yMinRayPos, points))
			{
				collidedObjects.push_back(object);
				continue;
			}
		}
		if (yMaxRayLength > 0)
		{
			glm::vec3 yMaxRayPos = ray.Position + (yMaxRayLength * ray.Normal);
			if (DoesRayHit(yMaxRayPos, points))
			{
				collidedObjects.push_back(object);
				continue;
			}
		}
		if (zMinRayLength > 0)
		{
			glm::vec3 zMinRayPos = ray.Position + (zMinRayLength * ray.Normal);
			if (DoesRayHit(zMinRayPos, points))
			{
				collidedObjects.push_back(object);
				continue;
			}
		}
		if (zMaxRayLength > 0)
		{
			glm::vec3 zMaxRayPos = ray.Position + (zMaxRayLength * ray.Normal);
			if (DoesRayHit(zMaxRayPos, points))
			{
				collidedObjects.push_back(object);
				continue;
			}
		}
	}

	return collidedObjects;
}

bool Physics::Raycast::DoesRayHit(glm::vec3 rayPos, vector<glm::vec3> aabbOuterPoints)
{
	// Check if ray falls short
	if (rayPos.x < aabbOuterPoints[0].x)
	{
		return false;
	}
	// Check if ray goes too far
	if (rayPos.x > aabbOuterPoints[1].x)
	{
		return false;
	}
	if (rayPos.y < aabbOuterPoints[0].y)
	{
		return false;
	}
	if (rayPos.y > aabbOuterPoints[1].y)
	{
		return false;
	}
	if (rayPos.z < aabbOuterPoints[0].z)
	{
		return false;
	}
	if (rayPos.z > aabbOuterPoints[1].z)
	{
		return false;
	}
	return true;
}
