#pragma once
#include <vector>
#include "GameObject.h"
#include "Unit.h"

using namespace std;
class SpawnManager
{
public:
	static SpawnManager* Instance();
	void Spawn(Unit unitToSpawn, int spawnPosId);


private:
	SpawnManager() {};
	SpawnManager(SpawnManager const&) {};
	SpawnManager& operator=(SpawnManager const&) {};
	static SpawnManager* m_pInstance;

	vector<GameObject> m_spawnPoints;
};

