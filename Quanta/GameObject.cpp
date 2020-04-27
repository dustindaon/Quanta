#include "GameObject.h"

unsigned int GameObject::m_idCounter;

GameObject::GameObject(string name, Model model, Shader shader)
{
	m_name = name;
	SetModel(model);
	SetShader(shader);
	isEmpty = false;
	GameObject();
}

GameObject::GameObject()
{
	SetID(GameObject::m_idCounter);
}

void GameObject::Update()
{
}

void GameObject::SetID(unsigned int id)
{
	m_id = id;
	GameObject::m_idCounter++;
}

Model& GameObject::GetModel()
{
	return m_model;
}

void GameObject::SetModel(Model model)
{
	m_model = model;
}

Shader& GameObject::GetShader()
{
	return m_shader;
}

void GameObject::SetShader(Shader shader)
{
	m_shader = shader;
}

Transform& GameObject::GetTransform()
{
	return m_transform;
}

void GameObject::SetTransform(Transform transform)
{
	m_transform = transform;
}

unsigned int GameObject::GetID()
{
	return m_id;
}

