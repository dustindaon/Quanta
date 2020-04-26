#include "SpawnManager.h"
#include <cstddef>

SpawnManager* SpawnManager::m_pInstance = NULL;
SpawnManager* SpawnManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new SpawnManager;
	}
	return m_pInstance;
}

void SpawnManager::Spawn(Unit unitToSpawn, int spawnPosId)
{

}
