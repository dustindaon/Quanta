#pragma once
#include <memory>
#include <vector>
#include "Scene.h"

using namespace std;
class Game : public GameObject
{
public:
	Game() {}
	virtual ~Game() {}

	virtual void StartGame() = 0;
	virtual shared_ptr<Scene> GetScene(int index) = 0;
	virtual shared_ptr<Scene> GetCurrentScene() = 0;
	virtual vector<shared_ptr<GameObject>> GetGameObjects() = 0;


	void AddScene(shared_ptr<Scene> newScene);
	vector<shared_ptr<Scene>> GetScenes();
private:
	vector<shared_ptr<Scene>> m_scenes;
};

