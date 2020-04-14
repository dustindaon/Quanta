#include "Transform.h"

Transform::Transform()
{
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_rotation = glm::vec3();
	m_position = glm::vec3();
}

glm::vec3 Transform::GetScale()
{
	return m_scale;
}

glm::vec3 Transform::GetRotation()
{
	return m_rotation;
}

glm::vec3 Transform::GetPosition()
{
	return m_position;
}

void Transform::SetScale(glm::vec3 newScale)
{
	m_scale = newScale;
}

void Transform::SetScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}

void Transform::SetRotation(glm::vec3 newRotation)
{
	m_rotation = newRotation;
}

void Transform::SetRotation(float x, float y, float z)
{
	m_rotation = glm::vec3(x, y, z);
}

void Transform::SetPosition(glm::vec3 newPosition)
{
	m_position = newPosition;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position = glm::vec3(x, y, z);
}
