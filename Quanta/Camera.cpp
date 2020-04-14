#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera* Camera::MainCamera = new Camera();

Camera::Camera()
{
	Initiate();
}

void Camera::Initiate()
{
	// Set inital position a few units back from origin
	Transform* initalTransform = new Transform();
	initalTransform->SetPosition(0.0f, 0.0f, -3.0f);

	// Set the initial rotation to point the camera toward negative z-axis
	// (90-degree clockwise rotation via yaw)
	initalTransform->SetRotation(-90.0f, 0.0f, 0.0f);
	m_transform = initalTransform;

	// Set inital facing to be towards center
	m_facing = glm::vec3(0.0f, 0.0f, -1.0f);

	// Set inital facing to be towards center
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_worldUp = m_up;

	UpdateCameraVectors();
}

Transform* Camera::GetTransform()
{
	return m_transform;
}

void Camera::SetMainCamera(Camera *newMainCamera)
{
	Camera::MainCamera = newMainCamera;
}

glm::mat4 Camera::GenerateViewMatrix()
{
	UpdateCameraVectors();
	
	return glm::lookAt(m_transform->GetPosition(), m_transform->GetPosition() + m_facing, m_up);
}

void Camera::UpdateCameraVectors()
{
	// Update the facing
	m_facing.x = cos(glm::radians(m_transform->GetRotation().x * cos(glm::radians(m_transform->GetRotation().y))));
	//m_facing.y = sin(glm::radians(m_transform->GetRotation().y));
	m_facing.z = sin(glm::radians(m_transform->GetRotation().x * cos(glm::radians(m_transform->GetRotation().y))));
	m_facing = glm::normalize(m_facing);

	// Recalculate camera right and front
	m_right = glm::normalize(glm::cross(m_facing, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_facing));
}

glm::vec3 Camera::GetFacing()
{
	return m_facing;
}

void Camera::SetFacing(glm::vec3 newFacing)
{
	m_facing = newFacing;
}

glm::vec3 Camera::GetUp()
{
	return m_up;
}

void Camera::SetUp(glm::vec3 newUp)
{
	m_up = newUp;
}

glm::vec3 Camera::GetWorldUp()
{
	return m_worldUp;
}

glm::vec3 Camera::GetRight()
{
	return m_right;
}

void Camera::SetRight(glm::vec3 newRight)
{
	m_right = newRight;
}
