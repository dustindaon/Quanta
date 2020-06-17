#include "RenderingManager.h"
#include "Engine.h"
#include "CondorsNest.h"
#include <iostream>
#include "Mesh.h"

using namespace std;


int main()
{
	Engine::Instance()->Start(static_pointer_cast<Game>(CondorsNest::Instance()));

	return 0;
}

