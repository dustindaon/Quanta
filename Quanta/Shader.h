#pragma once

#include <string>
#include <iostream>
#include <vector>

#define BASIC_VERTEX_SHADER_PATH "Basic.vs";
#define BASIC_FRAGMENT_SHADER_PATH "Basic.fs";

using namespace std;
class Shader
{
public:
	string basicVertShaderPath = BASIC_VERTEX_SHADER_PATH;
	string basicFragShaderPath = BASIC_FRAGMENT_SHADER_PATH;

	Shader(string vertexFilePath, string fragmentFilePath);
	Shader(string vertexFilePath);
	Shader();

	void AddVertexShaderFile(string pathName);
	void AddFragmentShaderFile(string pathname);

	void SetBool(const string& name, bool value) const;
	void SetInt(const string& name, int value) const;
	void SetFloat(const string& name, float value) const;

	unsigned int LoadShaders();

private:
	vector<string> vertexShaderFiles;
	vector<string> fragmentShaderFiles;

	unsigned int m_ID;
	bool m_isLoaded = false;
};

