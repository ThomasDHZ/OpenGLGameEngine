#pragma once
#include <vector>
#include "Vertex.h"
#include "GLManager.h"

class Mesh
{
private:
	unsigned int VertexCount;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

public:
	Mesh();
	Mesh(const std::vector<Vertex>& VertexList, const std::vector<unsigned int>& IndiceList, GLManager& manager);
	~Mesh();

	Mesh& operator=(const Mesh& rhs);

	void Update(GLManager& manager);
	void DeleteBuffers();
};

