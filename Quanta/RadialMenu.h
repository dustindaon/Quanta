#pragma once
#include "UI.h"
#include "SpawnManager.h"

class RadialMenu :
	public UI
{
public:
	RadialMenu(vector<shared_ptr<Unit>> units);
	bool HandleClick(weak_ptr<GameObject> cursor);
	void CreateMenu();

//	// TODO: Move these out
//	void AddNewUnitType(Unit unitToAdd);
//	vector<Unit> GetUnitTypes();
//
//	// Variables for handling game state
//// TODO: Remove this from here
////bool m_radialBuyMenuActive = false;
////shared_ptr<RadialMenu> m_activeMenu;
	vector<shared_ptr<Unit>> m_unitTypes;

private:
	void DestroyMenu();

	float m_menuRadius = 3;
};

