#pragma once
#include "Game.h"
#include "InputHandler.h"

class FortTortuga: public Game
{
public:
	void Update(float deltaTime);
	void StartGame();

	shared_ptr<Scene> GetScene(int index);
	shared_ptr<Scene> GetCurrentScene();
	vector<shared_ptr<GameObject>> GetGameObjects();

private:
	InputHandler m_inputHandler;
};

