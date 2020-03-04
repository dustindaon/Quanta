#pragma once
#include <string>

using namespace std;
class GameObject
{
public:
	void Update();
	GameObject(string name);
	GameObject();

	void SetID(unsigned int id) {
		m_id = id;
		GameObject::m_idCounter++;
	}
	unsigned int GetID() {
		return m_id;
	}

private:
	unsigned int m_id;
	static unsigned int m_idCounter;
	string m_name;
};


