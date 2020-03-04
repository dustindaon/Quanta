#include "Engine.h"
#include <iostream>

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

void Engine::Start()
{
	cout << "Start your engine!" << endl;
	Engine::Instance()->Update();
}

void Engine::Update()
{
	cout << "Updating" << endl;
	while (m_isRunning)
	{
		for (weak_ptr<GameObject> _gameObject : m_gameObjects)
		{
			if (!_gameObject.expired())
			{
				_gameObject.lock()->Update();
			}
		}

		m_isRunning = false;
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

// Returns a weak_ptr<GameObject> from the list of GameObjects stored in Engine
// NOTES: For most tasks, should get GameObject from GameManager class instead
weak_ptr<GameObject> Engine::GetGameObject(unsigned int id)
{
	return m_gameObjects[id];
}

// Returns a vector of all weak_ptr<GameObject> kept in Engine
// NOTES: For most tasks, should get GameObjects from GameManager class instead
vector<weak_ptr<GameObject>> Engine::GetGameObjects()
{
	return m_gameObjects;
}

// Returns a vector of a subset of weak_ptr<GameObject>'s kept in Engine
// NOTES: For most tasks, should get GameObjects from GameManager class instead
vector<weak_ptr<GameObject>> Engine::GetGameObjects(vector<unsigned int> ids)
{
	return m_gameObjects;
}
