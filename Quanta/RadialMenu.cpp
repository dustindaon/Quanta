#include "RadialMenu.h"

RadialMenu::RadialMenu(vector<shared_ptr<Unit>> units)
{
	m_unitTypes = units;
}

bool RadialMenu::HandleClick(weak_ptr<GameObject> cursor)
{
	DestroyMenu();
	return true;
}

void RadialMenu::CreateMenu()
{
	float menuCircumference = 3.14159f * (m_menuRadius * m_menuRadius);
	float distBetweenItems = menuCircumference / m_unitTypes.size();

	// Populate the radial menu with evenly spaced out units that the player can buy
	for (int i = 0; i < m_unitTypes.size(); ++i)
	{
		//Model unitSprite = 
	}
}

void RadialMenu::DestroyMenu()
{
}
