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
	// Create cursor
	// TODO: Should be in it's own class, maybe a Command
	Model cursorSprite = Model("Resources/Cursor/cursor_up_128.png", true);
	shared_ptr<GameObject> cursor = make_shared<GameObject>("NormalCursor", cursorSprite);
	cursor->GetTransform().SetScale(0.004, 1, 0.004);
	m_globalObjects.push_back(cursor);
	m_inputHandler = InputHandler();
	m_inputHandler.Initialize(cursor);

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
	for (int i = 0; i < m_globalObjects.size(); ++i)
	{
		objects.push_back(m_globalObjects[i]);
	}
	objects.push_back(shared_from_this());

	return objects;
}
