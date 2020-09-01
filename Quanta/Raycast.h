#pragma once
#include "Engine.h"
#include "Vector4.h"

namespace Physics
{
	class Raycast
	{
	public:
		// Pass in a vertex ray with the normal representing the direction of the ray
		static vector<shared_ptr<GameObject>> CastRay(Vertex ray, float length);
		static vector<shared_ptr<GameObject>> CastRay(Vertex ray, float length, vector<shared_ptr<GameObject>> targets);
		static bool DoesRayHit(glm::vec3 rayPos, vector<glm::vec3> aabbOuterPoints);
	};
}

