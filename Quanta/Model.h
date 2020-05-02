#include <vector>
#include <string>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include <memory>

using namespace std;
#pragma once
class Model
{
public:
	Model();
	Model(string const& modelFilePath);
	Model(string const& spriteFilePath, bool isSprite);
	void LoadModel(string const& modelFilePath);
	void Load2DModel(string spriteFilePath);
	void Draw(Shader shader);


	//void LoadTexture(const char* filePath);
	//void SetModelData(vector<vector<Vector4>> data);
	//vector<vector<Vector4>> GetModelData();
	//unsigned char* GetTextureData();
	//vector<vector<float>> GetTexturePoints();

	//int GetTextureWidth();
	//int GetTextureHeight();
	//int GetTextureColourChannels();
	//int GetTextureID();
	//void SetTextureID(unsigned int ID);

private:
	vector<Mesh> m_meshes;
	string m_directory;
	glm::vec2 m_spriteSize;

	void ProcessAssimpNode(aiNode* node, const aiScene* scene);
	Mesh ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene);

	vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	unsigned int LoadTextureFromFile(string& path);

	//string m_modelFilePath;
	//const char* m_texFilePath;
	//unsigned char* m_texData;
	//int m_texWidth;
	//int m_texHeight;
	//int m_numColourChannels;
	//unsigned int m_texID;
	//vector<vector<Vector4>> m_modelPoints;
	//vector<vector<float>> m_texPoints;
};

