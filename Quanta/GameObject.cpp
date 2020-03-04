#include "GameObject.h"

unsigned int GameObject::m_idCounter;

void GameObject::Update()
{
}

GameObject::GameObject(string name)
{
	SetID(GameObject::m_idCounter);
}

GameObject::GameObject()
{
	SetID(GameObject::m_idCounter);
}

