#include "RadialMenu.h"

RadialMenu::RadialMenu()
{
}

bool RadialMenu::HandleClick(weak_ptr<GameObject> cursor)
{
	DestroyMenu();
	return true;
}

void RadialMenu::CreateMenu()
{
	vector<Unit> menuUnits;
	float menuCircumference = 3.14159f * (m_menuRadius * m_menuRadius);
	float distBetweenItems = menuCircumference / menuUnits.size();

	for (int i = 0; i < menuUnits.size(); ++i)
	{

	}
}

void RadialMenu::DestroyMenu()
{
}