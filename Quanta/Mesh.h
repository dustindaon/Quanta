#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

using namespace std;
class Mesh
{
public:
	Mesh(vector<Vertex> verts, vector<unsigned int> indices, vector<Texture> textures);

	vector<Vertex> vertices;
	vector<unsigned int> vertIndices;
	vector<Texture> textures;

	void Draw(Shader shader);

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;

	void Initialize();
};

