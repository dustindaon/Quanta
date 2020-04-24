#include "FortTortuga.h"
#include "FirstLevel.h"
#include <fstream>
#include "Shader.h"

void FortTortuga::StartGame()
{
	AddScene(make_shared<FirstLevel>());
}

shared_ptr<Scene> FortTortuga::GetScene(int index)
{
	return GetScenes()[index];
}

shared_ptr<Scene> FortTortuga::GetCurrentScene()
{
	return GetScenes()[0];
}
