#include "Engine.h"
#include <iostream>
#include "RenderingManager.h"

using namespace std;

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

	game->StartGame();

	Engine::Instance()->Update(game);
}

void Engine::Update(shared_ptr<Game> game)
{
	float lastFrame = 0.0f;

	while (m_isRunning)
	{
		m_gameObjects = game->GetGameObjects();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		for (shared_ptr<GameObject> _gameObject : m_gameObjects)
		{
			_gameObject->Update(deltaTime);
		}
		RenderingManager::Instance()->Update();
	}
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

