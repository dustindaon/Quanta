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

void InputHandler::Initialize(shared_ptr<GameObject> cursorSprite)
{
	// Set mouse callback so we know when the mouse moves
	GLFWwindow* mainWindow = RenderingManager::Instance()->GetMainWindow();

	glfwSetCursorPosCallback(mainWindow, mouse_callback);
	glfwSetScrollCallback(mainWindow, scroll_callback);
	//glfwSetCursorPos(mainWindow, lastMouseX, lastMouseY);
	//lastMouseX = RenderingManager::Instance()->GetScreenWidth() / 2;
	//lastMouseY = RenderingManager::Instance()->GetScreenHeight() / 2;

	m_cursorSprite = cursorSprite;
}

Command* InputHandler::HandleInput(float deltaTime)
{
	ProcessKeys(deltaTime);
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

void InputHandler::ProcessKeys(float deltaTime)
{
	GLFWwindow* mainWindow = RenderingManager::Instance()->GetMainWindow();

	if (glfwGetKey(mainWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(mainWindow, true);
	}

	shared_ptr<Transform> mainCamera = Camera::MainCamera->GetTransform();
	float cameraSpeed = 1.0f * deltaTime;
	if (glfwGetKey(mainWindow, GLFW_KEY_W) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() + cameraSpeed * Camera::MainCamera->GetUp());
	if (glfwGetKey(mainWindow, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() - cameraSpeed * Camera::MainCamera->GetUp());
	if (glfwGetKey(mainWindow, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() - Camera::MainCamera->GetRight() * cameraSpeed);
	if (glfwGetKey(mainWindow, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() + Camera::MainCamera->GetRight() * cameraSpeed);
	if (glfwGetKey(mainWindow, GLFW_KEY_E) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() - Camera::MainCamera->GetFacing() * cameraSpeed * 2.0f);
	if (glfwGetKey(mainWindow, GLFW_KEY_Q) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() + Camera::MainCamera->GetFacing() * cameraSpeed * 2.0f);
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

		// Rotate the camera and cursor to match
		Camera::MainCamera->GetTransform()->SetRotation(cameraRot);
		m_mouseMoved = false;
		//m_cursorSprite->GetTransform().SetRotation(0, -cameraRot.x + 50, 0);

//#if _DEBUG
//		//glm::vec3 newPos = { Camera::MainCamera->GetTransform()->GetPosition().x, 0, Camera::MainCamera->GetTransform()->GetPosition().z };
//
//		//auto mouseTest = Engine::Instance()->GetGameObject(1);
//		//mouseTest->GetTransform().SetPosition(newPos);
//		cout << "X Position: " << Camera::MainCamera->GetTransform()->GetPosition().x << ", Z Position: " << Camera::MainCamera->GetTransform()->GetPosition().z << endl;
//#endif // _DEBUG
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

	//float cursorX = Camera::MainCamera->GetTransform()->GetPosition().x + (m_mousePos.x * 0.001);
	//float cursorY = Camera::MainCamera->GetTransform()->GetPosition().y - 0.15;
	//float cursorZ = Camera::MainCamera->GetTransform()->GetPosition().z + (m_mousePos.y * 0.001);
	float cursorX = Camera::MainCamera->GetTransform()->GetPosition().x + (m_mousePos.y * 0.000125);
	float cursorY = Camera::MainCamera->GetTransform()->GetPosition().y - 0.15;
	float cursorZ = Camera::MainCamera->GetTransform()->GetPosition().z - (m_mousePos.x * 0.000166);
	m_cursorSprite->GetTransform().SetPosition(cursorX, cursorY, cursorZ);
}

