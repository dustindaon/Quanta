#include "Game.h"

void Game::AddScene(shared_ptr<Scene> newScene)
{
	m_scenes.push_back(newScene);
}

vector<shared_ptr<Scene>> Game::GetScenes()
{
	return m_scenes;
}
