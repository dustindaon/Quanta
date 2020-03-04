#include "FirstLevel.h"
#include "SandCastlesManager.h"

FirstLevel::FirstLevel()
{
	auto enemy = make_shared<GameObject>();
	auto enemy2 = make_shared<GameObject>();
	auto enemy3 = make_shared<GameObject>();
	m_sceneObjects.push_back(enemy);
	m_sceneObjects.push_back(enemy2);
	m_sceneObjects.push_back(enemy3);

	SandCastlesManager::Instance()->AddGameObjects(m_sceneObjects);
}
