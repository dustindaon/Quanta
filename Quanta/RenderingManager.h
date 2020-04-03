#pragma once
#include <glad/glad.h> // Always include first!
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Engine.h"
#include "Matrix4.h"

// TESTING
#include "Shader.h"

using namespace std;
class RenderingManager
{
public:
	void Initiatiate();
	void ProcessInput(GLFWwindow* window);
	void static FramebufferSizeCallback(GLFWwindow* window, int width, int height);

private:
	glm::mat4 GenerateTransforms(weak_ptr<GameObject> parentObj);
};



