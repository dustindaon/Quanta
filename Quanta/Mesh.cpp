#include <glad/glad.h> // Always include first!
#include <GLFW/glfw3.h>
#include "Mesh.h"


Mesh::Mesh(vector<Vertex> verts, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = verts;
	this->vertIndices = indices;
	this->textures = textures;

	Initialize();
}


void Mesh::Initialize()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertIndices.size() * sizeof(unsigned int), &vertIndices[0], GL_STATIC_DRAW);

	// Create a 'pointer' to a data type within our array and tell how to extract that data from the array.
	// There can be many like position, colour, etc. Then we enable that attribute.
	// 0: Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// 1: Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(float)));
	// 2: Color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(float)));
	// 3: Texture
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(10 * sizeof(float)));

	glBindVertexArray(0);
}


void Mesh::Draw(Shader shader)
{
	unsigned int diffuseNumber = 1;
	unsigned int specularNumber = 1;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		// Activate proper texture unit before binding
		glActiveTexture(GL_TEXTURE0 + i);
		// Retrieve texture number (the N in diffuse_textureN)
		string number;
		string name = textures[i].textureType;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNumber);
			diffuseNumber++;
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNumber);
			specularNumber++;
		}

		shader.SetFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// Draw mesh
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, vertIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
