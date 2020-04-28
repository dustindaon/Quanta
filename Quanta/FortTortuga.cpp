#include "FortTortuga.h"
#include "FirstLevel.h"
#include <fstream>
#include "Shader.h"

void FortTortuga::Update(float deltaTime)
{
	m_inputHandler.HandleInput(deltaTime);
}

void FortTortuga::StartGame()
{
	m_inputHandler = InputHandler();
	AddScene(make_shared<FirstLevel>());
}

shared_ptr<Scene> FortTortuga::GetScene(int index)
{
	return GetScenes()[index];
}

shared_ptr<Scene> FortTortuga::GetCurrentScene()
{
	return GetScenes()[0];
}

vector<shared_ptr<GameObject>> FortTortuga::GetGameObjects()
{
	vector<shared_ptr<GameObject>> objects = GetCurrentScene()->GetGameObjects();
	objects.push_back(GetCurrentScene());
	objects.push_back(shared_from_this());

	return objects;
}
