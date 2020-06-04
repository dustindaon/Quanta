#include "FirstLevel.h"
#include "Camera.h"

#include "Swordsman.h"
#include "Archer.h"
#include "Catapult.h"

void FirstLevel::Update()
{

}

FirstLevel::FirstLevel()
{
	CreateEnemies();

	// Create a map sprite and rotate it into postion (got all the positions on the map from a previous ver,
	// so we have to rotate the map to fit the old coordinates)
	Shader standard = Shader("Standard.vs", "Standard.fs");
	Model mapModel = Model("Resources/RoughDraft/map_sprite.png", true);
	auto map = make_shared<GameObject>("Map", mapModel, standard);
	map->GetTransform().SetRotation(0, 180, 0);

	// Set the camera above the level pointing down at it
	Camera::MainCamera->GetTransform()->SetPosition(0.0f, 1.5f, 0.0f);
	Camera::MainCamera->GetTransform()->SetRotation(0.0f, -90.0f, 0.0f);

	AddGameObject(map);
}

void FirstLevel::PopulatePurchasableUnits()
{
}

void FirstLevel::HandleCommands(vector<shared_ptr<Command>> commands)
{
	for (int i = 0; i < commands.size(); ++i)
	{
		commands[i]->Execute();
	}
}

shared_ptr<GameObject> FirstLevel::GetObjectAtLocation(glm::vec2 location)
{
	vector<shared_ptr<GameObject>> sceneObjects = GetGameObjects();

	for (int i = 0; i < sceneObjects.size(); ++i)
	{
		glm::vec2 objectPos = glm::vec2(sceneObjects[i]->GetTransform().GetPosition().x, sceneObjects[i]->GetTransform().GetPosition().z);
		float collisionDist = 0.5f;

		cout << "(" << location.x << ", " << location.y << "), (" << objectPos.x << ", " << objectPos.y << ")" << endl;
		cout << (objectPos - location).length() << endl;
		if ((objectPos - location).length() <= collisionDist)
		{
			return sceneObjects[i];
		}
	}
	return nullptr;
}

void FirstLevel::CreateEnemies()
{
	glm::vec3 p1Start = { 0.666, 0, 0.590 };
	glm::vec3 p2Start = { -0.456, 0, 0.458 };
	glm::vec3 p3Start = { -0.824, 0, 0.01 };
	glm::vec3 p4Intersect = { 0.226, 0, 0.038 };
	glm::vec3 p5Intersect = { 0.285, 0, -0.301 };
	glm::vec3 p6Intersect = { 0.103, 0, -0.475 };
	glm::vec3 p7Intersect = { -0.082, 0, -0.63 };
	glm::vec3 p8End = { 0.899, 0, -0.572 };
	glm::vec3 p9End = { 0.693, 0, -0.652 };
	glm::vec3 p10End = { 0.404, 0, -0.79 };
	glm::vec3 p11End = { 0.316, 0, -0.97 };
	glm::vec3 p12Road = { 0.251, 0, 0.225 };
	glm::vec3 p13Road = { 0.899, 0, -0.060 };
	glm::vec3 p14Road = { 0.119, 0, -0.644 };
	glm::vec3 p15Road = { -0.134, 0, -0.900 };

	vector<vector<glm::vec3>> startRoutes = { {p1Start, p12Road, p4Intersect}, {p2Start, p4Intersect}, {p3Start, p7Intersect} };
	vector<vector<glm::vec3>> midRoutes = { {p4Intersect, p5Intersect}, {p5Intersect, p4Intersect}, {p5Intersect, p6Intersect}, {p6Intersect, p5Intersect}, {p6Intersect, p7Intersect}, {p7Intersect, p6Intersect} };
	vector<vector<glm::vec3>> endRoutes = { {p4Intersect, p13Road, p8End}, {p5Intersect, p9End}, {p6Intersect, p14Road, p10End}, {p7Intersect, p15Road, p11End} };
	
	glm::vec3 spawnLoc1 = { p1Start };
	glm::vec3 spawnLoc2 = { p2Start };
	glm::vec3 spawnLoc3 = { p3Start };

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


	AddGameObjects({ enemy1, enemy2, enemy3 });

	vector<glm::vec3> newRoute(startRoutes[0]);
	newRoute.insert(newRoute.end(), midRoutes[0].begin()+1, midRoutes[0].end());
	newRoute.insert(newRoute.end(), endRoutes[1].begin()+1, endRoutes[1].end());

	enemy1->SetRoute(newRoute);
	enemy1->SetMovementSpeed(0.2f);
}

//Start Point 1: 0.666, 0.590
//Start Point 2 : -0.456, 0.458
//Start Point 3 : -0.824, 0.01
//Intersection 4 : 0.226, 0.038
//Intersection 5 : 0.285, -0.301
//Intersection 6 : 0.103, -0.475
//Intersection 7 : -0.082, -0.63
//End Point 8 : 0.899, -0.572
//End Point 9 : 0.693, -0.652
//End Point 10 : 0.404, -0.79
//End Point 11 : 0.316, -0.97
//Road Point 12 : 0.251, 0.225
//Road Point 13 : 0.899, -0.060
//Road Point 14 : 0.119, -0.644
//Road Point 15 : -0.134, -0.900
//
//Routes : START : [1, 12, 4] , [2, 4], [3, 7]
//INTERSECTIONS : [4, 5] , [5, 4], [5, 6], [6, 5], [6, 7], [7, 6]
//END : [4, 13, 8] , [5, 9], [6, 14, 10], [7, 15, 11]