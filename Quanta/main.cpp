#include "RenderingManager.h"
#include "Engine.h"
#include "FortTortuga.h"
#include <iostream>
#include "Mesh.h"

using namespace std;
int main()
{
	shared_ptr<FortTortuga> fortTortuga = make_shared<FortTortuga>();

	Engine::Instance()->Start(static_pointer_cast<Game>(fortTortuga));

	return 0;
}