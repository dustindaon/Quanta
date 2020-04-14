#pragma once
#include "Transform.h"
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	Transform* GetTransform();
	static void SetMainCamera(Camera *newMainCamera);
	static Camera* MainCamera;

	float fieldOfView = 45.0f;

	glm::mat4 GenerateViewMatrix();
	void UpdateCameraVectors();

	glm::vec3 GetFacing();
	void SetFacing(glm::vec3 newFacing);
	glm::vec3 GetUp();
	void SetUp(glm::vec3 newUp);
	glm::vec3 GetWorldUp();
	glm::vec3 GetRight();
	void SetRight(glm::vec3 newRight);

private: 
	void Initiate();
	glm::vec3 m_facing;
	glm::vec3 m_up;
	glm::vec3 m_worldUp;
	glm::vec3 m_right;

	Transform* m_transform;
};

