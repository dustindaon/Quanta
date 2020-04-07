#include "FirstLevel.h"
#include "SandCastlesManager.h"

FirstLevel::FirstLevel()
{
	Model bigModel = Model("big", "Resources/container.jpg");
	Model smallModel = Model("small", "Resources/container.jpg");

	Shader blue = Shader("Standard.vs", "Standard.fs");
	Shader red = Shader("Standard.vs", "Standard.fs");
	
	auto triangle = make_shared<GameObject>("BIG!", bigModel, blue);
	auto triangleSmall = make_shared<GameObject>("SMOLL!", smallModel, red);

	triangle->GetTransform().SetPosition(Vector4(0.25f, 0.0f, 0.0f));
	triangle->GetTransform().SetRotation(Vector4(0.0f, 0.0f, 1.0f));
	triangleSmall->GetTransform().SetPosition(Vector4(0.25f, 0.5f, 0.0f));
	triangleSmall->GetTransform().SetScale(Vector4(2.0f, 3.0f, 0.0f));

	m_sceneObjects.push_back(triangle);
	m_sceneObjects.push_back(triangleSmall);

	SandCastlesManager::Instance()->AddGameObjects(m_sceneObjects);
}
