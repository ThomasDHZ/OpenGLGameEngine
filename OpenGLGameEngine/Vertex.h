#pragma once
#include <glm/glm.hpp>

enum VertexMap
{
	Pos,
	Color,
	TextureCoord
};

struct Vertex
{
	glm::vec3 Position = glm::vec3(0.0f);
};