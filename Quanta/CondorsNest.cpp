#include "CondorsNest.h"
#include "FirstLevel.h"
#include <fstream>
#include "Shader.h"

// Commands
#include "ScrollCommand.h"

CondorsNest* CondorsNest::m_pInstanceRaw = NULL;
shared_ptr<CondorsNest> CondorsNest::m_pInstance;
shared_ptr<CondorsNest> CondorsNest::Instance()
{
	if (!m_pInstanceRaw)
	{
		m_pInstanceRaw = new CondorsNest;
		m_pInstance = shared_ptr<CondorsNest> (m_pInstanceRaw);
	}
	return m_pInstance;
}

void CondorsNest::Update(float deltaTime)
{
	vector<shared_ptr<Command>> commands = m_inputHandler->HandleInput(deltaTime);
	GetCurrentScene()->HandleCommands(commands);
}

void CondorsNest::StartGame()
{
	// Create cursor
	// TODO: Should be in it's own class, maybe a Command
	shared_ptr<GameObject> cursor = CreateCursor();
	m_globalObjects.push_back(cursor);
	SetupInputCommands(cursor);
	AddScene(make_shared<FirstLevel>());
}

shared_ptr<Scene> CondorsNest::GetScene(int index)
{
	return GetScenes()[index];
}

shared_ptr<Scene> CondorsNest::GetCurrentScene()
{
	return GetScenes()[0];
}

vector<shared_ptr<GameObject>> CondorsNest::GetGameObjects()
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

bool CondorsNest::CheckIfLocationIsValid(glm::vec2 location)
{
	shared_ptr<Scene> currentScene = GetCurrentScene();
	shared_ptr<GameObject> clickedObject = currentScene->GetObjectAtLocation(location);

	if (clickedObject == nullptr)
	{
		return false;
	}
	else
	{
		cout << clickedObject->GetName() << endl;
	}

	return true;
}

void CondorsNest::SetupInputCommands(shared_ptr<GameObject> cursor)
{
	m_inputHandler = make_shared<InputHandler>();
	m_inputHandler->Initialize(cursor);
}

shared_ptr<GameObject> CondorsNest::CreateCursor()
{
	Model cursorSprite = Model("Resources/Cursor/cursor_up_128.png", true);
	shared_ptr<GameObject> cursor = make_shared<GameObject>("NormalCursor", cursorSprite);
	cursor->GetTransform().SetScale(0.004, 1, 0.004);

	return cursor;
}
