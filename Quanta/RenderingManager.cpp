#include "RenderingManager.h"


using namespace std;

void RenderingManager::Initiatiate() 
{
	// Initialize GLFW and specify what version of OpenGL we want to use
	// Also, tell it we're using CORE version, which is the one with more control
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Make the window object and give it dimensions
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create OPENGL window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	// Load GLAD and tell it where the location of the OpenGL function pointers are
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Tell OpenGL the size of the rendering window for coordinates/display
	// First two parameters are bottom left of window, last two are top right
	// NOTES: OpenGL converts coordinates to (-1, 1) for both dimensions. (0, 0) = middle of screen.
	glViewport(0, 0, 800, 600);

	// Tell GLFW about our callback method that resizes the viewport when window is resized
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	// Create a Vertex Array Object which allows us to more dynamically swap 3D objects to render than just a VBO does
	vector<unsigned int> vertexArrObjs;

	// Go through all our Models and bind them to a VBO and then that to a VAO
	// TODO: Put this process in the Model object
	vector<weak_ptr<GameObject>> gameObjects = vector<weak_ptr<GameObject>>();
	gameObjects = Engine::Instance()->GetGameObjects();
	int objCounter = 0;
	for (weak_ptr<GameObject> gameObject : gameObjects)
	{
		if (!gameObject.expired())
		{
			unsigned int vertexArrObj;
			glGenVertexArrays(1, &vertexArrObj);
			glBindVertexArray(vertexArrObj);

			// TODO: Make this load more than the first mesh in a GameObject's Model
			vector<Vector4> vecModelData = gameObject.lock()->GetModel().GetData()[0];
			vector<float> vecModelFloats;
			for (Vector4 vec : vecModelData)
			{
				vecModelFloats.push_back(vec.GetX());
				vecModelFloats.push_back(vec.GetY());
				vecModelFloats.push_back(vec.GetZ());
			}

			// Create a vertex buffer to store all our 3D verts
			unsigned int vertexBuffObj;
			glGenBuffers(1, &vertexBuffObj);

			// Copy vertex array into a buffer
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffObj);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vecModelFloats.size(), vecModelFloats.data(), GL_STATIC_DRAW);

			// Create a 'pointer' to a data type within our array and tell how to extract that data from the array.
			// There can be many like position, colour, etc. Then we enable that attribute.
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// Add VAO to our list
			vertexArrObjs.push_back(vertexArrObj);
		}

		objCounter++;
	}

	// Wireframes to see objects more clearly!
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Render loop to keep drawing screen until window is closed
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Roll through our game objects, loading each's unique shader and enabling the VAO for each model
		// Then create a transformation matrix and pass it to our shaders
		// TODO: Loading shaders like this is very ineffiecient. Either put all shaders together into one file
		// OR create a list of already existing shaders and load objects that share the same shader in groups
		int vaoCounter = 0;
		for (weak_ptr<GameObject> gameObject : gameObjects)
		{
			unsigned int shaderProgram = gameObject.lock()->GetShader().LoadShaders();
			glUseProgram(shaderProgram);
			glm::mat4 transforms = GenerateTransforms(gameObject);
			unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transforms));

			glBindVertexArray(vertexArrObjs[vaoCounter]);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			vaoCounter++;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

// Close window if user hits 'Esc'
void RenderingManager::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

// Callback method used when a window is resized so the viewport resizes with it
void RenderingManager::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

glm::mat4 RenderingManager::GenerateTransforms(weak_ptr<GameObject> parentObj)
{
	Transform parent = parentObj.lock()->GetTransform();
	Vector4 position = parent.GetPosition();
	Vector4 scale = parent.GetScale();
	Vector4 rotation = parent.GetRotation();
	glm::mat4 transformation = glm::mat4(1.0f);

	// Transform its scale
	transformation = glm::scale(transformation, glm::vec3(scale.GetX(), scale.GetY(), scale.GetZ()));

	// Transform its rotation through X, Y, and Z
	transformation = glm::rotate(transformation, rotation.GetX(), glm::vec3(1.0, 0.0, 0.0));
	transformation = glm::rotate(transformation, rotation.GetY(), glm::vec3(0.0, 1.0, 0.0));
	transformation = glm::rotate(transformation, rotation.GetZ(), glm::vec3(0.0, 0.0, 1.0));

	// Transform its position
	transformation = glm::translate(transformation, glm::vec3(position.GetX(), position.GetY(), position.GetZ()));

	return transformation;

	//Matrix4 transformation = Matrix4();
	//// Transform its scale
	//transformation = transformation * Matrix4(true, false, false, scale.GetX(), scale.GetY(), scale.GetZ());

	//// Transform its rotation through X, Y, and Z
	//transformation = transformation * Matrix4(false, false, true, rotation.GetX(), 0, 0);
	//transformation = transformation * Matrix4(false, false, true, 0, rotation.GetY(), 0);
	//transformation = transformation * Matrix4(false, false, true, 0, 0, rotation.GetZ());

	//// Transform its position
	//transformation = transformation * Matrix4(false, true, false, position.GetX(), position.GetY(), position.GetZ());
	//
	//for (Vector4 &point : pointData)
	//{
	//	point = transformation * point;
	//}
}