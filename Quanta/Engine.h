#pragma once
// Creation Date: Feb 9th, 2020
// Description: Engine class is the heart of the game engine,
// it's a singleton so as to enforce there only being one.
// Bugs: None
// TODO: Implement update and start.
#include <vector>
#include <memory>
#include "GameObject.h"

using namespace std;
class Engine
{
public:
	static Engine* Instance();
	void Start();
	void Update();

	void AddGameObject(shared_ptr<GameObject>);
	void AddGameObjects(vector<shared_ptr<GameObject>>);
	void RemoveGameObject(unsigned int _id);
	void RemoveGameObjects(vector<unsigned int> _ids);
	weak_ptr<GameObject> GetGameObject(unsigned int _id);
	vector<weak_ptr<GameObject>> GetGameObjects();
	vector<weak_ptr<GameObject>> GetGameObjects(vector<unsigned int> _ids);

private:
	Engine() {};
	Engine(Engine const&) {};
	Engine& operator=(Engine const&) {};
	static Engine* m_pInstance;
	// When set to false, Engine halts all operations
	bool m_isRunning = false;
	// The set of GameObjects passed from a GameManager that need to be initialized and updated
	vector<weak_ptr<GameObject>> m_gameObjects;
};

