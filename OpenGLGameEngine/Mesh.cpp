#include "Mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\ext\matrix_transform.hpp>

Mesh::Mesh()
{
	VertexCount = 0;
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

Mesh::Mesh(const std::vector<Vertex>& VertexList, const std::vector<unsigned int>& IndiceList, GLGraphicsManager& manager)
{
	ModelMatrix = glm::mat4(1.0f);
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f);

	VertexCount = VertexList.size();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	manager.BindVAO(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vertex), &VertexList[0], GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(IndiceList), &IndiceList[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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

void Mesh::Update(GLGraphicsManager& manager)
{
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, Position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, Scale);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	if (manager.GetVAOID() != VAO)
	{
		manager.BindVAO(VAO);
	}

	manager.SetShaderModelValue(ModelMatrix);

	glDrawArrays(GL_TRIANGLES, 0, 36);
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

void Mesh::SetModelMatrix(const glm::mat4 modelMatrix)
{
	ModelMatrix = modelMatrix;
}

void Mesh::SetPosition(const float x, const float y, const float z)
{
	Position = glm::vec3(x, y, z);
}

void Mesh::SetPosition(const glm::vec3 position)
{
	Position = position;
}

void Mesh::SetRotation(const float x, const float y, const float z)
{
	Rotation = glm::vec3(x, y, z);
}

void Mesh::SetRotation(const glm::vec3 rotation)
{
	Rotation = rotation;
}

void Mesh::SetRotationX(const float x)
{
	Rotation.x = x;
}

void Mesh::SetRotationY(const float y)
{
	Rotation.y = y;
}

void Mesh::SetRotationZ(const float z)
{
	Rotation.z = z;
}

void Mesh::SetScale(const float x, const float y, const float z)
{
	Scale = glm::vec3(x, y, z);
}

void Mesh::SetScale(const glm::vec3 scale)
{
	Scale = scale;
}