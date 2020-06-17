#pragma once
#include "Game.h"
#include "InputHandler.h"

class CondorsNest: public Game
{
public:
	static shared_ptr<CondorsNest> Instance();

	void Update(float deltaTime);
	void StartGame();

	shared_ptr<Scene> GetScene(int index);
	shared_ptr<Scene> GetCurrentScene();
	vector<shared_ptr<GameObject>> GetGameObjects();

	bool CheckIfLocationIsValid(glm::vec2 location);

private:
	static CondorsNest* m_pInstanceRaw;
	static shared_ptr<CondorsNest> m_pInstance;

	void SetupInputCommands(shared_ptr<GameObject> cursor);
	shared_ptr<GameObject> CreateCursor();

	shared_ptr<InputHandler> m_inputHandler;
	vector<shared_ptr<GameObject>> m_globalObjects;
};

