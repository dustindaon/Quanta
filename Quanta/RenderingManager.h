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
#include "Camera.h"

// TESTING
#include "Shader.h"

using namespace std;
class RenderingManager
{
public:
	static RenderingManager* Instance();

	void static FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void Update();

	float GetScreenWidth();
	float GetScreenHeight();
	GLFWwindow* GetMainWindow();

private:
	RenderingManager() {};
	RenderingManager(RenderingManager const&) {};
	RenderingManager& operator=(RenderingManager const&) {};
	static RenderingManager* m_pInstance;

	vector<glm::mat4> GenerateTransforms(weak_ptr<GameObject> parentObj);
	GLFWwindow *m_mainWindow;

	void Initiate();

	float m_screenWidth;
	float m_screenHeight;
};



