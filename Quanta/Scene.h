#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>

using namespace std;
class Scene : public GameObject
{
public:
	void AddGameObject(shared_ptr<GameObject>);
	void AddGameObjects(vector<shared_ptr<GameObject>>);
	vector<shared_ptr<GameObject>> GetGameObjects();

private:
	vector<shared_ptr<GameObject>> m_sceneObjects;
};

