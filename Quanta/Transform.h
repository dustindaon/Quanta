#pragma once
#include "Component.h"
#include "Vector4.h"

class Transform : public Component
{
	public:
		Transform();

		Vector4 GetScale();
		Vector4 GetRotation();
		Vector4 GetPosition();

		void SetScale(Vector4 newScale);
		void SetRotation(Vector4 newRotation);
		void SetPosition(Vector4 newPosition);
		void SetPosition(float x, float y, float z);

	private:
		Vector4 m_scale;
		Vector4 m_rotation;
		Vector4 m_position;
};

