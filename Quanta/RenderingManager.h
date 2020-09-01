#pragma once
#include <glad/glad.h> // Always include first!
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Engine.h"
#include "Matrix4.h"
#include "Camera.h"

////////////////////////////////////////////////////////////
// RenderingManager Class
// Usage: Singleton that can be called using RenderingManager::Instance(). Used to iterate
// through all GameObjects in our world and renders them given the Model/View/Projection matrices
/////////////////////////////////////////////////////////////
class RenderingManager
{
public:
	static RenderingManager* Instance();

	void static FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void Update();

	float GetScreenWidth();
	float GetScreenHeight();
	weak_ptr<GLFWwindow> GetMainWindow();

private:
	RenderingManager() {};
	RenderingManager(RenderingManager const&) {};
	RenderingManager& operator=(RenderingManager const&) {};
	static RenderingManager* m_pInstance;

	vector<glm::mat4> GenerateTransforms(weak_ptr<GameObject> parentObj);
	shared_ptr<GLFWwindow> m_mainWindow;

	void Initiate();

	float m_screenWidth = 0;
	float m_screenHeight = 0;
};



