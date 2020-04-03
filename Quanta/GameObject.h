#pragma once
#include <string>
#include <vector>
#include "Model.h"
#include "Vector4.h"
#include "Shader.h"
#include "Transform.h"

using namespace std;
class GameObject
{
public:
	void Update();
	GameObject(string name, Model model, Shader shader);
	GameObject();

	unsigned int GetID();
	void SetID(unsigned int id);

	Model& GetModel();
	void SetModel(Model model);

	Shader& GetShader();
	void SetShader(Shader shader);

	Transform& GetTransform();
	void SetTransform(Transform transform);

private:
	unsigned int m_id;
	static unsigned int m_idCounter;
	string m_name;
	Model m_model;
	Shader m_shader;
	Transform m_transform;
};


