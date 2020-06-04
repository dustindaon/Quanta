#pragma once
#include "Scene.h"
#include "InputHandler.h"

class FirstLevel :
	public Scene
{
	public:
		void Update();
		FirstLevel();
		void PopulatePurchasableUnits();

		void HandleCommands(vector<shared_ptr<Command>> commands);
		shared_ptr<GameObject> GetObjectAtLocation(glm::vec2 location);

	private:
		void CreateEnemies();
		unique_ptr<InputHandler> m_inputHandler;
};

