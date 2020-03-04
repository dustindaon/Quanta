#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>

using namespace std;
class Scene
{
public:
	vector<shared_ptr<GameObject>> m_sceneObjects;
};

