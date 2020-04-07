#include <vector>
#include "Vector4.h"
#include <string>

using namespace std;
#pragma once
class Model
{
public:
	Model();
	Model(string modelFilePath);
	Model(string modelFilePath, const char* textureFilePath);
	void LoadModel(string filePath);
	void LoadTexture(const char* filePath);
	void SetModelData(vector<vector<Vector4>> data);
	vector<vector<Vector4>> GetModelData();
	unsigned char* GetTextureData();
	vector<vector<float>> GetTexturePoints();
	int GetTextureWidth();
	int GetTextureHeight();
	int GetTextureColourChannels();
	int GetTextureID();
	void SetTextureID(unsigned int ID);

private:
	string m_modelFilePath;
	const char* m_texFilePath;
	unsigned char* m_texData;
	int m_texWidth;
	int m_texHeight;
	int m_numColourChannels;
	unsigned int m_texID;
	vector<vector<Vector4>> m_modelPoints;
	vector<vector<float>> m_texPoints;
};

