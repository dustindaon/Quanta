#pragma once
class GameObject
{
public:
	void Update();


	void SetID(unsigned int id) {
		m_id = id;
	}
	unsigned int GetID() {
		return m_id;
	}


private:
	unsigned int m_id;
};

