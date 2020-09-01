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

	// Returns m_aabbPoints
	vector<glm::vec3> GetAABB();

	// 2 vec3's that represent the outermost vertices on the object. 
	// 1st vector = (minX, minY, minZ), 2nd = (maxX, maxY, maxZ)
	vector<glm::vec3> m_outerPoints = vector<glm::vec3>{ glm::vec3(1000, 1000, 1000),
														glm::vec3(-1000, -1000, -1000) };
private:
	vector<Mesh> m_meshes;
	glm::vec2 m_spriteSize = glm::vec2(0, 0);

	// A vector of vec3's that represent the points on a cube surrounding the object
	// 1st 4 vec3's = one face (vec3, vec3, vec3, vec3), 2nd 4 vec3's = opposite face (vec3, vec3, vec3, vec3)
	vector<glm::vec3> m_aabbPoints;
	string m_directory;

	unsigned int m_id;

	void ProcessAssimpNode(aiNode* node, const aiScene* scene);
	Mesh ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene);

	void CalcMinMaxPoint(glm::vec3 point);

	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	unsigned int LoadTextureFromFile(string& path);
};

