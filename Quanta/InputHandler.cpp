#include "InputHandler.h"

glm::vec2 InputHandler::m_mousePos;
glm::vec2 InputHandler::m_mouseOldPos = glm::vec2(0.0f, 0.0f);
glm::vec2 InputHandler::m_mouseScroll;
bool InputHandler::m_mouseScrolled = false;
bool InputHandler::m_mouseMoved = false;

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	InputHandler::SetMousePos(glm::vec2(xPos, yPos));
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	InputHandler::SetMouseScroll(glm::vec2(xOffset, yOffset));
}

Command* InputHandler::HandleInput()
{
	GLFWwindow* mainWindow = RenderingManager::Instance()->GetMainWindow();
	// Set mouse callback so we know when the mouse moves
	glfwSetCursorPosCallback(mainWindow, mouse_callback);
	glfwSetScrollCallback(mainWindow, scroll_callback);
	//glfwSetCursorPos(mainWindow, lastMouseX, lastMouseY);
	//lastMouseX = RenderingManager::Instance()->GetScreenWidth() / 2;
	//lastMouseY = RenderingManager::Instance()->GetScreenHeight() / 2;

	ProcessKeys();
	ProcessMouse();

	return NULL;
}

void InputHandler::SetMousePos(glm::vec2 newPos)
{
	m_mouseOldPos = m_mousePos;
	m_mousePos = newPos;

	m_mouseMoved = true;
}

glm::vec2 InputHandler::GetMousePos()
{
	return m_mousePos;
}

void InputHandler::SetMouseScroll(glm::vec2 newScroll)
{
	m_mouseScroll = newScroll;
	m_mouseScrolled = true;
}

glm::vec2 InputHandler::GetMouseScroll()
{
	return m_mouseScroll;
}

void InputHandler::ProcessKeys()
{
	GLFWwindow* mainWindow = RenderingManager::Instance()->GetMainWindow();

	if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mainWindow, true);
	}

	shared_ptr<Transform> mainCamera = Camera::MainCamera->GetTransform();
	float cameraSpeed = 1.0f * Engine::Instance()->deltaTime;
	if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() + cameraSpeed * Camera::MainCamera->GetUp());
	if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() - cameraSpeed * Camera::MainCamera->GetUp());
	if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() - Camera::MainCamera->GetRight() * cameraSpeed);
	if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() + Camera::MainCamera->GetRight() * cameraSpeed);
}

void InputHandler::ProcessMouse()
{
	if (m_mouseMoved)
	{
		float xOffset = m_mousePos.x - m_mouseOldPos.x;
		float yOffset = m_mouseOldPos.y - m_mousePos.y;

		const float sensitivity = 0.05f;
		xOffset *= sensitivity;
		yOffset *= sensitivity;

		// Figure out the new rotation, and lock the y-axis so the camera can't do flips
		glm::vec3 cameraRot = Camera::MainCamera->GetTransform()->GetRotation();
		cameraRot.x = glm::mod(cameraRot.x + xOffset, 360.0f);

		// Lock up/down rotations
		//cameraRot.y += yOffset;

		//if (cameraRot.y > 89.0f)
		//	cameraRot.y = 89.0f;
		//if (cameraRot.y < -89.0f)
		//	cameraRot.y = -89.0f;

		Camera::MainCamera->GetTransform()->SetRotation(cameraRot);
		m_mouseMoved = false;

#if _DEBUG
		cout << "X Position: " << Camera::MainCamera->GetTransform()->GetPosition().x << ", Y Position: " << Camera::MainCamera->GetTransform()->GetPosition().y << endl;
#endif // _DEBUG
	}

	if (m_mouseScrolled)
	{
		shared_ptr<Transform> trans = Camera::MainCamera->GetTransform();

		float fov = Camera::MainCamera->fieldOfView;

		if (fov >= 1.0f && fov <= 45.0f)
			fov -= m_mouseScroll.y;
		else if (fov <= 1.0f)
			fov = 1.0f;
		else if (fov >= 45.0f)
			fov = 45.0f;

		Camera::MainCamera->fieldOfView = fov;
		m_mouseScrolled = false;
	}
}

