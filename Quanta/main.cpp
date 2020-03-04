#include "Engine.h"
#include "SandCastlesManager.h"
#include <iostream>

using namespace std;
int main()
{
	Engine::Instance()->Start();
	SandCastlesManager::Instance();
	cout << SandCastlesManager::Instance()->m_sceneList.size() << endl;
	cout << SandCastlesManager::Instance()->m_sceneList[0].use_count() << endl;
	cout << Engine::Instance()->GetGameObject(0).lock()->GetID() << endl;

	SandCastlesManager::Instance()->m_sceneList.clear();
	cout << Engine::Instance()->GetGameObject(0).lock()->GetID() << endl;



	int n = 0;
	cin >> n;
	
	return 0;
}