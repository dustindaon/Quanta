#pragma once
#include "Component.h"
#include "Vector4.h"
#include <glm/vec3.hpp>

class Transform : public Component
{
	public:
		Transform();

		glm::vec3 GetScale();
		glm::vec3 GetRotation();
		glm::vec3 GetPosition();

		void SetScale(glm::vec3 newScale);
		void SetScale(float x, float y, float z);
		void SetRotation(glm::vec3 newRotation);
		void SetRotation(float x, float y, float z);
		void SetPosition(glm::vec3 newPosition);
		void SetPosition(float x, float y, float z);

	private:
		glm::vec3 m_scale;
		glm::vec3 m_rotation;
		glm::vec3 m_position;
};

