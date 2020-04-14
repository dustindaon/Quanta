#include "FirstLevel.h"
#include "SandCastlesManager.h"
#include "Camera.h"

FirstLevel::FirstLevel()
{
	Model charModel = Model("Resources/nanosuit.obj");

	Shader standard = Shader("Standard.vs", "Standard.fs");
	
	auto character = make_shared<GameObject>("BIG!", charModel, standard);
	//auto character1 = make_shared<GameObject>("Guy!", charModel, standard);
	//auto character2 = make_shared<GameObject>("Another!", charModel, standard);
	//auto character3 = make_shared<GameObject>("MORE!", charModel, standard);
	//auto character4 = make_shared<GameObject>("SOMANY!", charModel, standard);

	//character->GetTransform().SetScale(0.1f, 0.1f, 0.1f);
	//character->GetTransform().SetRotation(Vector4(0.0f, 2.0f, 0.0f));

	//character1->GetTransform().SetScale(Vector4(0.1f, 0.1f, 0.1f));
	//character1->GetTransform().SetPosition(Vector4(10.0f, 6.0f, 0.0f));
	//character1->GetTransform().SetRotation(Vector4(1.0f, 0.0f, 0.0f));

	//character2->GetTransform().SetScale(Vector4(0.1f, 0.1f, 0.1f));
	//character2->GetTransform().SetPosition(Vector4(-7.0f, 0.0f, 0.0f));
	//character2->GetTransform().SetRotation(Vector4(0.3f, 1.1f, 0.3f));

	//character3->GetTransform().SetScale(Vector4(0.1f, 0.1f, 0.1f));
	//character3->GetTransform().SetPosition(Vector4(2.5f, 8.1f, 0.8f));
	//character3->GetTransform().SetRotation(Vector4(0.0f, 2.0f, 0.1f));

	//character4->GetTransform().SetScale(Vector4(0.1f, 0.1f, 0.1f));
	//character4->GetTransform().SetPosition(Vector4(-5.9f, -5.8f, -5.0f));
	//character4->GetTransform().SetRotation(Vector4(0.0f, 0.0f, 2.0f));

	Camera::MainCamera->GetTransform()->SetPosition(0.0f, 0.0f, 10.0f);
	//Camera::MainCamera->GetTransform()->SetRotation(0.0f, 2.0f, 0.0f);

	m_sceneObjects.push_back(character);
	//m_sceneObjects.push_back(character1);
	//m_sceneObjects.push_back(character2);
	//m_sceneObjects.push_back(character3);
	//m_sceneObjects.push_back(character4);

	SandCastlesManager::Instance()->AddGameObjects(m_sceneObjects);
}
