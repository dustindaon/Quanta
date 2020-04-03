#include "Transform.h"

Transform::Transform()
{
	m_scale = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_rotation = Vector4();
	m_position = Vector4();
}

Vector4 Transform::GetScale()
{
	return m_scale;
}

Vector4 Transform::GetRotation()
{
	return m_rotation;
}

Vector4 Transform::GetPosition()
{
	return m_position;
}

void Transform::SetScale(Vector4 newScale)
{
	m_scale = newScale;
}

void Transform::SetRotation(Vector4 newRotation)
{
	m_rotation = newRotation;
}

void Transform::SetPosition(Vector4 newPosition)
{
	m_position = newPosition;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_position = Vector4(x, y, z);
}
