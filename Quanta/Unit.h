#pragma once
#include "GameObject.h"
class Unit : public GameObject
{
public:
	Unit(string name, Model model, Shader shader) : GameObject(name, model, shader) {};
	Unit();
};

