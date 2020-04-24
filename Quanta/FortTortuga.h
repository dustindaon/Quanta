#pragma once
#include "Game.h"

class FortTortuga: public Game
{
public:
	void StartGame();

	shared_ptr<Scene> GetScene(int index);
	shared_ptr<Scene> GetCurrentScene();

private:
};

