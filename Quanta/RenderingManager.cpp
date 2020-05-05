#include "RenderingManager.h"
#include "stb_image.h"

using namespace std;

RenderingManager* RenderingManager::m_pInstance = NULL;
RenderingManager* RenderingManager::Instance()
{
	if (!m_pInstance)
	{
		m_pInstance = new RenderingManager;
		m_pInstance->Initiate();
	}
	return m_pInstance;
}

void RenderingManager::Initiate() 
{
	m_screenWidth = 800;
	m_screenHeight = 600;

	// Initialize GLFW and specify what version of OpenGL we want to use
	// Also, tell it we're using CORE version, which is the one with more control
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Make the window object and give it dimensions
	m_mainWindow = glfwCreateWindow(m_screenWidth, m_screenHeight, "Fort Tortuga", NULL, NULL);
	if (m_mainWindow == NULL)
	{
		std::cout << "Failed to create OPENGL window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(m_mainWindow);

	// Load GLAD and tell it where the location of the OpenGL function pointers are
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Enable Z-Buffer
	glEnable(GL_DEPTH_TEST);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Tell OpenGL the size of the rendering window for coordinates/display
	// First two parameters are bottom left of window, last two are top right
	// NOTES: OpenGL converts coordinates to (-1, 1) for both dimensions. (0, 0) = middle of screen.
	glViewport(0, 0, m_screenWidth, m_screenHeight);

	// Tell GLFW about our callback method that resizes the viewport when window is resized
	glfwSetFramebufferSizeCallback(m_mainWindow, FramebufferSizeCallback);

	//// Wireframes to see objects more clearly!
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Disable cursor
	glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

//	// Lock the mouse inside the window
//	glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void RenderingManager::Update()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Roll through our game objects, loading each's unique shader and enabling the VAO for each model
	// Then create a transformation matrix and pass it to our shaders
	// TODO: Loading shaders like this is very ineffiecient. Either put all shaders together into one file
	// OR create a list of already existing shaders and load objects that share the same shader in groups
	vector<shared_ptr<GameObject>> gameObjects = Engine::Instance()->GetGameObjects();
	for (shared_ptr<GameObject> gameObject : gameObjects)
	{
		if (gameObject->isEmpty)
		{
			continue;
		}

		unsigned int shaderProgram = gameObject->GetShader().LoadShaders();
		glUseProgram(shaderProgram);

		gameObject->GetModel().Draw(gameObject->GetShader());

		vector<glm::mat4> transforms = GenerateTransforms(gameObject);
		unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
		unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
		unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transforms[0]));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(transforms[1]));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(transforms[2]));
	}

	glfwSwapBuffers(m_mainWindow);
	glfwPollEvents();
}

float RenderingManager::GetScreenWidth()
{
	return m_screenWidth;
}

float RenderingManager::GetScreenHeight()
{
	return m_screenHeight;
}

GLFWwindow* RenderingManager::GetMainWindow()
{
	return m_mainWindow;
}

// Callback method used when a window is resized so the viewport resizes with it
void RenderingManager::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

vector<glm::mat4> RenderingManager::GenerateTransforms(weak_ptr<GameObject> parentObj)
{
	Transform parent = parentObj.lock()->GetTransform();

	//// Generate Model Matrix
	glm::vec3 position = parent.GetPosition();
	glm::vec3 scale = parent.GetScale();
	glm::vec3 rotation = parent.GetRotation();
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	// Transform its position
	modelMatrix = glm::translate(modelMatrix, position);

	// Transform its rotation through X, Y, and Z
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));

	// Transform its scale
	modelMatrix = glm::scale(modelMatrix, scale);

	//// Generate View Matrix
	glm::mat4 viewMatrix = Camera::MainCamera->GenerateViewMatrix();

	//// Generate Projection Matrix (the frustrum that gives perspective to the scene)
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::perspective(glm::radians(Camera::MainCamera->fieldOfView), m_screenWidth / m_screenHeight, 0.1f, 100.0f);

	vector<glm::mat4> transforms = { modelMatrix, viewMatrix, projectionMatrix };

	return transforms;
}


