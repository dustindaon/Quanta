#include <vector>
#include "Vector4.h"
#include <string>

using namespace std;
#pragma once
class Model
{
public:
	Model();
	Model(string filePath);
	void LoadModel(string filePath);
	void SetData(vector<vector<Vector4>> data);
	vector<vector<Vector4>> GetData();

private:
	string m_modelFilePath;
	vector<vector<Vector4>> m_modelPoints;
};

