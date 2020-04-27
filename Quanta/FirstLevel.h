#pragma once
#include "Scene.h"

class FirstLevel :
	public Scene
{
	public:
		void Update();
		FirstLevel();

	private:
		void CreateEnemies();
};

