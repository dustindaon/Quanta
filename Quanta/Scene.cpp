#include "Scene.h"

// Takes a shared_ptr<GameObject> from a scene and registers it
void Scene::AddGameObject(shared_ptr<GameObject> objectToAdd)
{
	m_sceneObjects.push_back(objectToAdd);
}

// Takes a vector of shared_ptr<GameObject> from a scene and registers it
void Scene::AddGameObjects(vector<shared_ptr<GameObject>> objectsToAdd)
{
	m_sceneObjects.insert(m_sceneObjects.end(), objectsToAdd.begin(), objectsToAdd.end());
}

vector<shared_ptr<GameObject>> Scene::GetGameObjects()
{
	return m_sceneObjects;
}
