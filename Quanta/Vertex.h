#pragma once
#include <glm/glm.hpp>

class Vertex
{
public:
	Vertex();
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec4 color, glm::vec2 textureCoords);

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec4 Color;
	glm::vec2 TextureCoords;
};

