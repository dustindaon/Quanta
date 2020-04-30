#include <glad/glad.h> // Always include first!
#include <GLFW/glfw3.h>
#include "Model.h"

// For optimization purposes
vector<Texture> texturesLoaded;

Model::Model(string const& modelFilePath)
{
	LoadModel(modelFilePath);
}

Model::Model(string const& spriteFilePath, glm::vec2 spriteSize)
{
	Load2DModel(spriteFilePath, spriteSize);
}

Model::Model()
{

}

void Model::LoadModel(string const &filePath)
{
	Assimp::Importer modelImporter;
	const aiScene* scene = modelImporter.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene == NULL || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "Error from Assimp:: " << modelImporter.GetErrorString() << endl;
		return;
	}
	m_directory = filePath.substr(0, filePath.find_last_of('/'));

	ProcessAssimpNode(scene->mRootNode, scene);
}

// Creates a square sprite using a filepath as the sprite
// TODO: Add spritesheet functionality
void Model::Load2DModel(string spriteFilePath, glm::vec2 spriteSize)
{
	vector<Texture> sprites;

	bool skip = false;
	for (unsigned int j = 0; j < texturesLoaded.size(); j++)
	{
		// Already loaded our texture once
		if (texturesLoaded[j].path == spriteFilePath)
		{
			sprites.push_back(texturesLoaded[j]);
			skip = true;
			break;
		}
	}
	// If our texture hasn't been loaded already then load it
	if (!skip)
	{
		Texture sprite;
		// Assumes the texture file is located in the same directory as the model parent
		sprite.id = LoadTextureFromFile(spriteFilePath);
		sprite.textureType = aiTextureType_DIFFUSE;
		sprite.path = spriteFilePath;

		sprites.push_back(sprite);
	}
	
	vector<Vertex> verts;
	vector<unsigned int> indices;
	Mesh spriteMesh = Mesh(verts, indices, sprites);
	m_meshes.push_back(spriteMesh);
}

void Model::Draw(Shader shader)
{
	for (Mesh mesh : m_meshes)
	{
		mesh.Draw(shader);
	}
}

// To be used if you want to maintain the heirarchy/connectivity of meshes in the scene
void Model::ProcessAssimpNode(aiNode *node, const aiScene *scene)
{
	// Go through the meshes in each node
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(ProcessAssimpMesh(mesh, scene));
	}

	// Go through the rest of the nodes and process those
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessAssimpNode(node->mChildren[i], scene);
	}
}

Mesh Model::ProcessAssimpMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> verts;
	vector<unsigned int> indices;
	vector<Texture> textures;

	// Process vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vert;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vert.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vert.Normal = vector;

		if (mesh->HasVertexColors(0))
		{
			glm::vec4 colors;
			colors.r = mesh->mColors[0]->r;
			colors.g = mesh->mColors[0]->g;
			colors.b = mesh->mColors[0]->b;
			colors.a = mesh->mColors[0]->a;
			vert.Color = colors;
		}

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vert.TextureCoords = vec;
		}
		else
		{
			vert.TextureCoords = glm::vec2(0.0f, 0.0f);
		}
		verts.push_back(vert);
	}

	// Process indices
	for (int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// Process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
		vector<Texture> diffuseMaps = LoadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		vector<Texture> specularMaps = LoadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(verts, indices, textures);
}


vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString location;
		mat->GetTexture(type, i, &location);
		bool skip = false;
		for (unsigned int j = 0; j < texturesLoaded.size(); j++)
		{
			// Already loaded our texture once
			if (std::strcmp(texturesLoaded[j].path.data(), location.C_Str()) == 0)
			{
				textures.push_back(texturesLoaded[j]);
				skip = true;
				break;
			}
		}
		 // If our texture hasn't been loaded already then load it
		if (!skip)
		{
			Texture texture;
			// Assumes the texture file is located in the same directory as the model parent
			string filename = location.C_Str() + '/' + m_directory;

			texture.id = LoadTextureFromFile(filename);
			texture.textureType = typeName;
			texture.path = location.C_Str();
			textures.push_back(texture);
		}
	}
	return textures;
}

unsigned int Model::LoadTextureFromFile(string& path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// If this fails, likely that the Texture path is invalid
	int width, height, nrComponents;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGBA;
		if (nrComponents == 1)
		{
			format = GL_RED;
		}
		else if (nrComponents == 3)
		{
			format = GL_RGB;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
