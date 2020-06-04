#pragma once
#include <vector>
#include <memory>
#include "GameObject.h"
#include "Command.h"

using namespace std;
class Scene : public GameObject
{
public:
	void AddGameObject(shared_ptr<GameObject>);
	void AddGameObjects(vector<shared_ptr<GameObject>>);
	vector<shared_ptr<GameObject>> GetGameObjects();

	virtual void HandleCommands(vector<shared_ptr<Command>>) = 0;
	virtual shared_ptr<GameObject> GetObjectAtLocation(glm::vec2 location) = 0;

private:
	vector<shared_ptr<GameObject>> m_sceneObjects;
};

