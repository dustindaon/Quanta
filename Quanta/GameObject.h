#pragma once
#include <string>
#include <vector>
#include "Model.h"
#include "Shader.h"
#include "Component.h"
#include "Transform.h"

using namespace std;
class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject(string name, Model model, Shader shader);
	GameObject();

	virtual void Update(float deltaTime);

	unsigned int GetID();
	void SetID(unsigned int id);

	string GetName();
	void SetName(string name);

	Model& GetModel();
	void SetModel(Model model);

	Shader& GetShader();
	void SetShader(Shader shader);

	Transform& GetTransform();
	void SetTransform(Transform transform);

	bool isEmpty = true;

private:
	unsigned int m_id;
	static unsigned int m_idCounter;
	string m_name;
	Model m_model;
	Shader m_shader;
	Transform m_transform;
};


