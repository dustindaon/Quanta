#pragma once
#include "Scene.h"
#include "Engine.h"
#include <vector>
#include <memory>

using namespace std;
class SandCastlesManager
{
public:
	static SandCastlesManager* Instance();
	void AddScene(shared_ptr<Scene> newScene);
	void AddGameObject(shared_ptr<GameObject>);
	void AddGameObjects(vector<shared_ptr<GameObject>>);

	// TODO: Put in private
	vector<shared_ptr<Scene>> m_sceneList;
	vector<shared_ptr<GameObject>> m_gameObjects;

private:
	SandCastlesManager() {};
	SandCastlesManager(SandCastlesManager const&) {};
	SandCastlesManager& operator=(SandCastlesManager const&) {};

	void Initialize();

	static SandCastlesManager* m_pInstance;
};

