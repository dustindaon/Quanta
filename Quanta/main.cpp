#include "RenderingManager.h"
#include "Engine.h"
#include "Condor.h"
#include <iostream>
#include "Mesh.h"

using namespace std;
int main()
{
	//shared_ptr<Condor> Condor = make_shared<Condor>();
	Condor::Instance();
	Condor::Instance();

	Engine::Instance()->Start(static_pointer_cast<Game>(Condor::Instance()));

	return 0;
}