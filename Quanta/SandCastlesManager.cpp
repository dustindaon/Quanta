#include "SandCastlesManager.h"
#include "FirstLevel.h"

SandCastlesManager* SandCastlesManager::m_pInstance = NULL;
SandCastlesManager* SandCastlesManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new SandCastlesManager;
		m_pInstance->Initialize();
	}
	return m_pInstance;
}

void SandCastlesManager::Initialize()
{
	AddScene(make_shared<FirstLevel>());
}

void SandCastlesManager::AddScene(shared_ptr<Scene> newScene)
{
	m_sceneList.push_back(newScene);
}

// Takes a shared_ptr<GameObject> from a scene and registers it
void SandCastlesManager::AddGameObject(shared_ptr<GameObject> objectToAdd)
{
	m_gameObjects.push_back(objectToAdd);
	Engine::Instance()->AddGameObject(objectToAdd);
}

// Takes a vector of shared_ptr<GameObject> from a scene and registers it
void SandCastlesManager::AddGameObjects(vector<shared_ptr<GameObject>> objectsToAdd)
{
	m_gameObjects.insert(m_gameObjects.end(), objectsToAdd.begin(), objectsToAdd.end());
	Engine::Instance()->AddGameObjects(objectsToAdd);
}