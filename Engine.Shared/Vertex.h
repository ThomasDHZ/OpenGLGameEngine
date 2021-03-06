#pragma once
#include <glm/glm.hpp>

enum VertexMap
{
	Position,
	Normal,
	TextureCoord
};

struct Vertex
{
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Normal = glm::vec3(0.0f);
	glm::vec2 TextureCoord = glm::vec2(0.0f);
};
struct Vertex2
{
	glm::vec2 Position = glm::vec2(0.0f);
	glm::vec2 TextureCoord = glm::vec2(0.0f);
};