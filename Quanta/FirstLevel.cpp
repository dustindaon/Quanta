#include "FirstLevel.h"
#include "Camera.h"

FirstLevel::FirstLevel()
{
	Shader standard = Shader("Standard.vs", "Standard.fs");
	
	Model charModel = Model("Resources/nanosuit.obj");
	auto character = make_shared<GameObject>("Character", charModel, standard);

	Model mapModel = Model("Resources/RoughDraft/Map.obj");
	auto map = make_shared<GameObject>("Map", mapModel, standard);

	character->GetTransform().SetScale(0.01f, 0.01f, 0.01f);

	// Set the camera above the level pointing down at it
	Camera::MainCamera->GetTransform()->SetPosition(0.0f, 1.5f, 0.0f);
	Camera::MainCamera->GetTransform()->SetRotation(0.0f, -90.0f, 0.0f);

	AddGameObject(character);
	AddGameObject(map);
}
