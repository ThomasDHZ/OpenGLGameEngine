#include "Mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Mesh::Mesh()
{
	VertexCount = 0;
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

Mesh::Mesh(const std::vector<Vertex>& VertexList, const std::vector<unsigned int>& IndiceList, GLManager& manager)
{
	VertexCount = VertexList.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	manager.BindVAO(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vertex), &VertexList[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceList), &IndiceList[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	manager.BindVAO(0);
}

Mesh::~Mesh()
{
}

Mesh& Mesh::operator=(const Mesh& rhs)
{
	VertexCount = rhs.VertexCount;
	VAO = rhs.VAO;
	VBO = rhs.VBO;
	EBO = rhs.EBO;

	return *this;
}

void Mesh::Update(GLManager& manager)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	if (manager.GetVAOID() != VAO)
	{
		manager.BindVAO(VAO);
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Mesh::SetTextureID(unsigned int textureID)
{
	TextureID = textureID;
}

void Mesh::DeleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
