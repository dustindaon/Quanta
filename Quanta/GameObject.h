#pragma once
#include <string>
#include <vector>
#include "Model.h"
#include "Shader.h"
#include "Component.h"
#include "Transform.h"

using namespace std;

////////////////////////////////////////////////////////////
// GameObject Class
// Usage: When you want to make a new object in the game world, simply create
// a new class that is a child of GameObject and feed it a name, model, and shader
// (or leave it empty if it's an object that you just want to call updates with
// but don't actually desire any 3D rendering)
// =========================================================
// Params: 
// string: Name, used for filtering/searching
// Model: a Model object which gives the 3D data points for the model's structure
// Shader: Shader object is used to tell the rendering engine how the model should be drawn
/////////////////////////////////////////////////////////////
class GameObject : public enable_shared_from_this<GameObject>
{
public:
	// TODO: Create a static lookup of shaders and check to see if it exists first
	GameObject(string name, Model model, Shader shader);
	GameObject(string name, Model model);
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

	bool isEmpty = false;

private:
	unsigned int m_id;
	static unsigned int m_idCounter;
	string m_name;
	Model m_model;
	Shader m_shader;
	Transform m_transform;
};


