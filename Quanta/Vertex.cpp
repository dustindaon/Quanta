#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(glm::vec3 position, glm::vec3 normal, glm::vec4 color, glm::vec2 textureCoords)
{
	this->Position = position;
	this->Normal = normal;
	this->Color = color;
	this->TextureCoords = textureCoords;
}
