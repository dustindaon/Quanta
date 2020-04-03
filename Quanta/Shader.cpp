#include <glad/glad.h> // Always include first!
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include "Shader.h"

Shader::Shader(string vertexFilePath, string fragmentFilePath)
{
	AddVertexShaderFile(vertexFilePath);
	AddFragmentShaderFile(fragmentFilePath);
}

Shader::Shader(string vertexFilePath)
{
	AddVertexShaderFile(vertexFilePath);
	AddFragmentShaderFile(basicFragShaderPath);
}

Shader::Shader()
{
	AddVertexShaderFile(basicVertShaderPath);
	AddFragmentShaderFile(basicFragShaderPath);
}

void Shader::AddVertexShaderFile(string pathName)
{
	vertexShaderFiles.push_back(pathName);
}

void Shader::AddFragmentShaderFile(string pathName)
{
	fragmentShaderFiles.push_back(pathName);
}

unsigned int Shader::LoadShaders()
{
	// Create a shader program that combines multiple shaders and pipes the output of one shader to another
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	string vertexShaderData;
	ifstream vertexShaderFile;
	GLuint vertexShaderID;
	// Ensure ifstream objects can throw exceptions
	vertexShaderFile.exceptions(ifstream::badbit);

	// Go through all our vertex shaders
	for (int i = 0; i < vertexShaderFiles.size(); ++i)
	{
		// Open them one by one
		vertexShaderFile.open(vertexShaderFiles[i], ios::in);
		stringstream vertexStream;
		if (vertexShaderFile.is_open())
		{
			vertexStream << vertexShaderFile.rdbuf();
		}
		vertexShaderFile.close();

		// Load the data in the file into a const char*
		vertexShaderData = vertexStream.str();
		const GLchar* vertexShaderCData = vertexShaderData.c_str();

		// Create a new shader out of the data and compile it
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &vertexShaderCData, NULL);
		glCompileShader(vertexShaderID);

		// Check if the vertex shader worked
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
			std::cout << "Error: Vertex Shader Compilation FAILED \n" << infoLog << std::endl;
		}
		// Attach and delete now used shaders
		glAttachShader(shaderProgram, vertexShaderID);
		glDeleteShader(vertexShaderID);
	}

	string fragmentShaderData;
	ifstream fragmentShaderFile;
	GLuint fragmentShaderID;
	// Ensure ifstream objects can throw exceptions
	fragmentShaderFile.exceptions(ifstream::badbit);

	// Go through all our fragment shaders
	for (int i = 0; i < fragmentShaderFiles.size(); ++i)
	{
		// Open them one by one
		fragmentShaderFile.open(fragmentShaderFiles[i], ios::in);
		stringstream fragmentStream;
		if (fragmentShaderFile.is_open())
		{
			fragmentStream << fragmentShaderFile.rdbuf();
		}
		fragmentShaderFile.close();

		// Load the data in the file into a const char*
		fragmentShaderData = fragmentStream.str();
		const GLchar* fragmentShaderCData = fragmentShaderData.c_str();

		// Create a new shader out of the data and compile it
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentShaderCData, NULL);
		glCompileShader(fragmentShaderID);

		// Check if the fragment shader worked
		int success;
		char infoLog[512];
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
			std::cout << "Error: Fragment Shader Compilation FAILED \n" << infoLog << std::endl;
		}
		// Attach and delete now used shaders
		glAttachShader(shaderProgram, fragmentShaderID);
		glDeleteShader(fragmentShaderID);
	}

	glLinkProgram(shaderProgram);

	// Check if the shader program worked
	int shadProgSuccess;
	char shadProgInfoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shadProgSuccess);
	if (!shadProgSuccess)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, shadProgInfoLog);
		std::cout << "Error: Shader Program Linking FAILED \n" << shadProgInfoLog << std::endl;
	}

	return shaderProgram;
}
