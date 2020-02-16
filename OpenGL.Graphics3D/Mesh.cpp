#include "Mesh.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm\ext\matrix_transform.hpp>

EngineMesh::EngineMesh()
{
	VertexCount = 0;
	VAO = 0;
	VBO = 0;
	EBO = 0;
}

EngineMesh::EngineMesh(const std::vector<Vertex>& VertexList, const std::vector<unsigned int>& IndiceList)
{
	VertexCount = VertexList.size();

	ModelMatrix = glm::mat4(1.0f);
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(Vertex), &VertexList[0], GL_STATIC_DRAW);

	glBindVertexArray(VAO);

	glEnableVertexAttribArray(VertexMap::Position);
	glEnableVertexAttribArray(VertexMap::Normal);
	glEnableVertexAttribArray(VertexMap::TextureCoord);

	glVertexAttribPointer(VertexMap::Position, 3, GL_FLOAT, GL_FALSE, sizeof(VertexList), (void*)0);
	glVertexAttribPointer(VertexMap::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexList), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(VertexMap::TextureCoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexList), (void*)(6 * sizeof(float)));

}

EngineMesh::~EngineMesh()
{
}

EngineMesh& EngineMesh::operator=(const EngineMesh& rhs)
{
	VertexCount = rhs.VertexCount;
	IndiceCount = rhs.IndiceCount;
	TextureID = rhs.TextureID;
	VAO = rhs.VAO;
	VBO = rhs.VBO;
	EBO = rhs.EBO;
	
	Position = rhs.Position;
	Rotation = rhs.Rotation;
	Scale = rhs.Scale;
	ModelMatrix = rhs.ModelMatrix;
	return *this;
}

void EngineMesh::Update(unsigned int TextureIDz, Shader2 shader)
{
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, Position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, Scale);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureIDz);

	shader.setMat4("model", ModelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}

void EngineMesh::Update(unsigned int TextureIDz, unsigned int TextureIDz2, Shader2 shader)
{
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, Position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, Scale);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureIDz);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureIDz2);

	shader.setMat4("model", ModelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}

void EngineMesh::Update(unsigned int TextureIDz, unsigned int TextureIDz2, unsigned int ReflectionMap, Shader2 shader)
{
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, Position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, Scale);

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureIDz);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureIDz2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, ReflectionMap);

	shader.setMat4("model", ModelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}

void EngineMesh::SetTextureID(unsigned int textureID)
{
	TextureID = textureID;
}

void EngineMesh::DeleteBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void EngineMesh::SetModelMatrix(const glm::mat4 modelMatrix)
{
	ModelMatrix = modelMatrix;
}

void EngineMesh::SetPosition(const float x, const float y, const float z)
{
	Position = glm::vec3(x, y, z);
}

void EngineMesh::SetPosition(const glm::vec3 position)
{
	Position = position;
}

void EngineMesh::SetRotation(const float x, const float y, const float z)
{
	Rotation = glm::vec3(x, y, z);
}

void EngineMesh::SetRotation(const glm::vec3 rotation)
{
	Rotation = rotation;
}

void EngineMesh::SetRotationX(const float x)
{
	Rotation.x = x;
}

void EngineMesh::SetRotationY(const float y)
{
	Rotation.y = y;
}

void EngineMesh::SetRotationZ(const float z)
{
	Rotation.z = z;
}

void EngineMesh::SetScale(const float x, const float y, const float z)
{
	Scale = glm::vec3(x, y, z);
}

void EngineMesh::SetScale(const glm::vec3 scale)
{
	Scale = scale;
}