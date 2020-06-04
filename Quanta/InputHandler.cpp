#include "InputHandler.h"
#include "ScrollCommand.h"
#include "CreateRadialMenuCommand.h"
#include "Condor.h"

glm::vec2 InputHandler::m_mousePos;
glm::vec2 InputHandler::m_mouseOldPos = glm::vec2(0.0f, 0.0f);
glm::vec2 InputHandler::m_mouseScroll;
bool InputHandler::m_mouseDidScroll = false;
bool InputHandler::m_mouseDidMove = false;

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
	m_gameWindow = RenderingManager::Instance()->GetMainWindow();

	glfwSetCursorPosCallback(m_gameWindow.lock().get(), mouse_callback);
	glfwSetScrollCallback(m_gameWindow.lock().get(), scroll_callback);
	m_mouseOldPos.x = RenderingManager::Instance()->GetScreenWidth() / 2;
	m_mouseOldPos.y = RenderingManager::Instance()->GetScreenHeight() / 2;
	glfwSetCursorPos(m_gameWindow.lock().get(), m_mouseOldPos.x, m_mouseOldPos.y);

	m_cursorObject = move(cursorSprite);
}

vector<shared_ptr<Command>> InputHandler::HandleInput(float deltaTime)
{
	ProcessKeys(deltaTime);
	vector<shared_ptr<Command>> returnCommands = move(ProcessMouse());
	UpdateCursor();
	return returnCommands;
}

void InputHandler::SetMousePos(glm::vec2 newPos)
{
	m_mouseOldPos = m_mousePos;
	m_mousePos = newPos;

	m_mouseDidMove = true;
}

glm::vec2 InputHandler::GetMousePos()
{
	return m_mousePos;
}

void InputHandler::SetMouseScroll(glm::vec2 newScroll)
{
	m_mouseScroll = newScroll;
	m_mouseDidScroll = true;
}

glm::vec2 InputHandler::GetMouseScroll()
{
	return m_mouseScroll;
}

void InputHandler::ProcessKeys(float deltaTime)
{
	m_gameWindow = RenderingManager::Instance()->GetMainWindow();

	if (glfwGetKey(m_gameWindow.lock().get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_gameWindow.lock().get(), true);
	}

	shared_ptr<Transform> mainCamera = Camera::MainCamera->GetTransform();
	float cameraSpeed = 1.0f * deltaTime;
	if (glfwGetKey(m_gameWindow.lock().get(), GLFW_KEY_W) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() + cameraSpeed * Camera::MainCamera->GetUp());
	if (glfwGetKey(m_gameWindow.lock().get(), GLFW_KEY_S) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() - cameraSpeed * Camera::MainCamera->GetUp());
	if (glfwGetKey(m_gameWindow.lock().get(), GLFW_KEY_A) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() - Camera::MainCamera->GetRight() * cameraSpeed);
	if (glfwGetKey(m_gameWindow.lock().get(), GLFW_KEY_D) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() + Camera::MainCamera->GetRight() * cameraSpeed);
	if (glfwGetKey(m_gameWindow.lock().get(), GLFW_KEY_E) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() - Camera::MainCamera->GetFacing() * cameraSpeed * 2.0f);
	if (glfwGetKey(m_gameWindow.lock().get(), GLFW_KEY_Q) == GLFW_PRESS)
		mainCamera->SetPosition(mainCamera->GetPosition() + Camera::MainCamera->GetFacing() * cameraSpeed * 2.0f);
}

vector<shared_ptr<Command>> InputHandler::ProcessMouse()
{
	vector<shared_ptr<Command>> returnCommands;

	if (m_mouseDidMove)
	{
		HandleMouseMovement();
		m_mouseDidMove = false;
	}
	if (m_mouseDidScroll)
	{
		returnCommands.push_back(make_shared<ScrollCommand>(m_mouseScroll));
		m_mouseDidScroll = false;
	}
	if (glfwGetMouseButton(m_gameWindow.lock().get(), 0) == GLFW_RELEASE && m_mouseLeftDown)
	{
		shared_ptr<Command> leftClickCommand = HandleMouseLeftClick();
		if (leftClickCommand != NULL)
		{
			returnCommands.push_back(leftClickCmd);
		}
		m_mouseLeftDown = false;
	}
	else if (glfwGetMouseButton(m_gameWindow.lock().get(), 0))
	{
		m_mouseLeftDown = true;
	}
	if (glfwGetMouseButton(m_gameWindow.lock().get(), 1) == GLFW_RELEASE && m_mouseRightDown)
	{
		shared_ptr<Command> rightClickCommand = HandleMouseRightClick();
		if (rightClickCommand != NULL)
		{
			returnCommands.push_back(rightClickCommand);
		}
		m_mouseRightDown = false;
	}
	else if(glfwGetMouseButton(m_gameWindow.lock().get(), 1))
	{
		m_mouseRightDown = true;
	}

	return move(returnCommands);
}

void InputHandler::HandleMouseMovement()
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
	//Camera::MainCamera->GetTransform()->SetRotation(cameraRot);
	m_cursorObject->GetTransform().SetRotation(0, -cameraRot.x + 50, 0);

	//#if _DEBUG
	//		//glm::vec3 newPos = { Camera::MainCamera->GetTransform()->GetPosition().x, 0, Camera::MainCamera->GetTransform()->GetPosition().z };
	//
	//		//auto mouseTest = Engine::Instance()->GetGameObject(1);
	//		//mouseTest->GetTransform().SetPosition(newPos);
	//		cout << "X Position: " << Camera::MainCamera->GetTransform()->GetPosition().x << ", Z Position: " << Camera::MainCamera->GetTransform()->GetPosition().z << endl;
	//#endif // _DEBUG
}

shared_ptr<Command> InputHandler::HandleMouseLeftClick()
{
	glm::vec2 cursorPosition = glm::vec2(m_cursorObject->GetTransform().GetPosition().x, m_cursorObject->GetTransform().GetPosition().z);

	// Check if the target location is valid
	if (Condor::Instance()->CheckIfLocationIsValid(cursorPosition))
	{
		cout << "Yay!" << endl;
	}
	else
	{
		cout << "Boo!" << endl;
	}

	return leftClickCmd;
}

shared_ptr<Command> InputHandler::HandleMouseRightClick()
{
	cout << "Right click! X: " << m_cursorObject->GetTransform().GetPosition().x << ", Z: " << m_cursorObject->GetTransform().GetPosition().z << endl;

	return rightClickCmd;
}

void InputHandler::UpdateCursor()
{
	float cursorX = Camera::MainCamera->GetTransform()->GetPosition().x + (m_mousePos.y * 0.000207) - 0.06;
	float cursorY = Camera::MainCamera->GetTransform()->GetPosition().y - 0.15;
	float cursorZ = Camera::MainCamera->GetTransform()->GetPosition().z - (m_mousePos.x * 0.000207) + 0.08;
	m_cursorObject->GetTransform().SetPosition(cursorX, cursorY, cursorZ);
}

//void InputHandler::AddNewUnitType(Unit unitToAdd)
//{
//	m_unitTypes.push_back(unitToAdd);
//}
//
//vector<Unit> InputHandler::GetUnitTypes()
//{
//	return m_unitTypes;
//}