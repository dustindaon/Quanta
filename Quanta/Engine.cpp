#include "Engine.h"
#include <iostream>
#include "RenderingManager.h"

using namespace std;

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	float xOffset = xPos - Engine::Instance()->lastMouseX;
	float yOffset = Engine::Instance()->lastMouseY - yPos;
	Engine::Instance()->lastMouseX = xPos;
	Engine::Instance()->lastMouseY = yPos;

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

	shared_ptr<Transform> trans = Camera::MainCamera->GetTransform();
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	float fov = Camera::MainCamera->fieldOfView;

	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yOffset;
	else if (fov <= 1.0f)
		fov = 1.0f;
	else if (fov >= 45.0f)
		fov = 45.0f;

	Camera::MainCamera->fieldOfView = fov;
}

Engine* Engine::m_pInstance = NULL;
Engine* Engine::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Engine;
		Engine::Instance()->m_isRunning = true;
	}
	return m_pInstance;
}

void Engine::Start(shared_ptr<Game> game)
{
	RenderingManager::Instance();

	lastMouseX = RenderingManager::Instance()->GetScreenWidth() / 2;
	lastMouseY = RenderingManager::Instance()->GetScreenHeight() / 2;

	game->StartGame();

	Engine::Instance()->Update(game);
}

void Engine::Update(shared_ptr<Game> game)
{
	GLFWwindow* mainWindow = RenderingManager::Instance()->GetMainWindow();
	// Set mouse callback so we know when the mouse moves
	glfwSetCursorPosCallback(mainWindow, mouse_callback);
	glfwSetScrollCallback(mainWindow, scroll_callback);
	glfwSetCursorPos(mainWindow, lastMouseX, lastMouseY);

	float lastFrame = 0.0f;

	cout << "Updating" << endl;
	while (m_isRunning)
	{
		m_gameObjects = game->GetCurrentScene()->GetGameObjects();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ProcessInput();

		for (shared_ptr<GameObject> _gameObject : m_gameObjects)
		{
			_gameObject->Update();
		}
		RenderingManager::Instance()->Update();
	}
}

void Engine::ProcessInput()
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
}


// Takes a shared_ptr<GameObject> from GameManager and registers it as a weak_ptr<GameObject> in the engine
void Engine::AddGameObject(shared_ptr<GameObject> objectToAdd)
{
	m_gameObjects.push_back(objectToAdd);
}

// Takes a vector of shared_ptr<GameObject> from GameManager and registers it as a vector of weak_ptr<GameObject> in the engine
void Engine::AddGameObjects(vector<shared_ptr<GameObject>> objectsToAdd)
{
	m_gameObjects.insert(m_gameObjects.end(), objectsToAdd.begin(), objectsToAdd.end());
}

// Removes reference to GameObject in Engine
// NOTES: Should be removed from GameManager list of GameObjects
void Engine::RemoveGameObject(unsigned int id)
{
}

// Removes multiple references to GameObjects in Engine
// NOTES: Should be removed from GameManager list of GameObjects
void Engine::RemoveGameObjects(vector<unsigned int> ids)
{
}

// Returns a shared_ptr<GameObject> from the list of GameObjects stored in Engine
// NOTES: For most tasks, should get GameObject from Scene class instead
shared_ptr<GameObject> Engine::GetGameObject(unsigned int id)
{
	return m_gameObjects[id];
}

// Returns a vector of all shared_ptr<GameObject> kept in Engine
// NOTES: For most tasks, should get GameObjects from Scene class instead
vector<shared_ptr<GameObject>> Engine::GetGameObjects()
{
	return m_gameObjects;
}

// Returns a vector of a subset of shared_ptr<GameObject>'s kept in Engine
// NOTES: For most tasks, should get GameObjects from Scene class instead
vector<shared_ptr<GameObject>> Engine::GetGameObjects(vector<unsigned int> ids)
{
	return m_gameObjects;
}

