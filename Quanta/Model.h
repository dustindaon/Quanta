#pragma once
#include <vector>
#include <string>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include <memory>

using namespace std;

////////////////////////////////////////////////////////////
// Model Class
// Usage: Given a filepath, create and store either a 3D model or 2D sprite
// =========================================================
// Params: 
// string: Filepath to determine where to load the 3D geometry/textures from
// (optional) bool: If only wanting a 2D texture on a quad, set this to true
/////////////////////////////////////////////////////////////
class Model
{
public:
	Model();
	Model(string const& modelFilePath);
	Model(string const& spriteFilePath, bool isSprite);
	void LoadModel(string const& modelFilePath);
	void Load2DModel(string spriteFilePath);
	void Draw(Shader shader);

	void SetID(unsigned int id);
	unsigned int GetID();

private:
	vector<Mesh> m_meshes;
	string m_directory;
	glm::vec2 m_spriteSize;

	unsigned int m_id;

	void ProcessAssimpNode(aiNode* node, const aiScene* scene);
	Mesh ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene);

	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	unsigned int LoadTextureFromFile(string& path);
};

