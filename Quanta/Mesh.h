#pragma once
#include <vector>
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

using namespace std;

////////////////////////////////////////////////////////////
// Mesh Class
// Usage: 3D Models have one or more Meshes, which are created to store lik-geometry,
// as well as their associated textures
// =========================================================
// Params: 
// vector<Vertex>: Positional data on every unique vert in the mesh
// vector<unsigned int>: Int label used for effeciency, in case there are multiple of the same
// Vertex's used
// vector<Texture>: All the different Textures to be loaded (albedo, diffuse, etc)
/////////////////////////////////////////////////////////////
class Mesh
{
public:
	Mesh(vector<Vertex> verts, vector<unsigned int> indices, vector<Texture> textures);

	vector<Vertex> vertices;
	vector<unsigned int> vertIndices;
	vector<Texture> textures;

	void Draw(Shader shader);

	void SetID(unsigned int id);
	unsigned int GetID();

private:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_EBO;

	unsigned int m_id;

	void Initialize();
};

