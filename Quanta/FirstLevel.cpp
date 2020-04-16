#include "FirstLevel.h"
#include "SandCastlesManager.h"
#include "Camera.h"

FirstLevel::FirstLevel()
{
	Shader standard = Shader("Standard.vs", "Standard.fs");
	
	Model charModel = Model("Resources/nanosuit.obj");
	auto character = make_shared<GameObject>("Character", charModel, standard);

	Model mapModel = Model("Resources/RoughDraft/Map.obj");
	auto map = make_shared<GameObject>("Map", mapModel, standard);

	Camera::MainCamera->GetTransform()->SetPosition(0.0f, 0.0f, -3.0f);
	//Camera::MainCamera->GetTransform()->SetRotation(0.0f, 0.0f, 0.0f);

	m_sceneObjects.push_back(character);
	m_sceneObjects.push_back(map);


	SandCastlesManager::Instance()->AddGameObjects(m_sceneObjects);
}
