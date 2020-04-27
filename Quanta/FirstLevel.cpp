#include "FirstLevel.h"
#include "Camera.h"
#include "Unit.h"

void FirstLevel::Update()
{
}

FirstLevel::FirstLevel()
{
	CreateEnemies();
	Shader standard = Shader("Standard.vs", "Standard.fs");

	Model mapModel = Model("Resources/RoughDraft/Map.obj");
	auto map = make_shared<GameObject>("Map", mapModel, standard);

	// Set the camera above the level pointing down at it
	Camera::MainCamera->GetTransform()->SetPosition(0.0f, 1.5f, 0.0f);
	Camera::MainCamera->GetTransform()->SetRotation(0.0f, -90.0f, 0.0f);

	AddGameObject(map);
}

void FirstLevel::CreateEnemies()
{
	// Spawn Location 1-3 is the 3 enemy spawns, 4-6 is slightly offset from those spawns
	glm::vec3 spawnLoc1 = { 65, 0, 65 };
	glm::vec3 spawnLoc2 = { -48, 0, 50 };
	glm::vec3 spawnLoc3 = { -83, 0, 0 };
	//glm::vec3 spawnLoc4 = { 60, 0, 65 };
	//glm::vec3 spawnLoc5 = { -45, 0, 50 };
	//glm::vec3 spawnLoc6 = { -80, 0, 0 };
	// Crossroads 1-4 are the points where two paths meet/diverge from the bottom (coast) to the top
	glm::vec3 spawnLoc4 = { 5, 0, 0 };
	glm::vec3 spawnLoc5 = { -45, 0, 50 };
	glm::vec3 spawnLoc6 = { -80, 0, 0 };

	// Castle 1-4 are the points where the path ends at the castle

	Shader standard = Shader("Standard.vs", "Standard.fs");
	Model charModel = Model("Resources/nanosuit.obj");
	int enemyCount = 1;
	auto enemy1 = make_shared<Unit>("Enemy1", charModel, standard);
	enemy1->GetTransform().SetScale(0.01f, 0.01f, 0.01f);
	enemy1->GetTransform().SetPosition(spawnLoc1);

	auto enemy2 = make_shared<Unit>("Enemy2", charModel, standard);
	enemy2->GetTransform().SetScale(0.01f, 0.01f, 0.01f);
	enemy2->GetTransform().SetPosition(spawnLoc2);
	auto enemy3 = make_shared<Unit>("Enemy3", charModel, standard);
	enemy3->GetTransform().SetScale(0.01f, 0.01f, 0.01f);
	enemy3->GetTransform().SetPosition(spawnLoc3);
	auto enemy4 = make_shared<Unit>("Enemy4", charModel, standard);
	enemy4->GetTransform().SetScale(0.01f, 0.01f, 0.01f);
	enemy4->GetTransform().SetPosition(spawnLoc4);
	auto enemy5 = make_shared<Unit>("Enemy5", charModel, standard);
	enemy5->GetTransform().SetScale(0.01f, 0.01f, 0.01f);
	enemy5->GetTransform().SetPosition(spawnLoc5);
	auto enemy6 = make_shared<Unit>("Enemy6", charModel, standard);
	enemy6->GetTransform().SetScale(0.01f, 0.01f, 0.01f);
	enemy6->GetTransform().SetPosition(spawnLoc6);

	AddGameObjects({ enemy1, enemy2, enemy3, enemy4, enemy5, enemy6 });
}
