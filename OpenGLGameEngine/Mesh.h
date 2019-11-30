#pragma once
#include <vector>
#include "Vertex.h"
#include "GLGraphicsManager.h"

class Mesh
{
private:
	unsigned int VertexCount;
	unsigned int IndiceCount;
	unsigned int TextureID;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;
	glm::mat4 ModelMatrix;

public:
	Mesh();
	Mesh(const std::vector<Vertex>& VertexList, const std::vector<unsigned int>& IndiceList, GLGraphicsManager& manager);
	~Mesh();

	Mesh& operator=(const Mesh& rhs);

	void Update(GLGraphicsManager& manager);
	void SetTextureID(unsigned int textureID);
	void DeleteBuffers();

	void SetModelMatrix(const glm::mat4 modelMatrix);
	void SetPosition(const float x, const float y, const float z);
	void SetRotation(const float x, const float y, const float z);
	void SetScale(const float x, const float y, const float z);
	void SetPosition(const glm::vec3 position);
	void SetRotation(const glm::vec3 rotation);
	void SetScale(const glm::vec3 scale);
	void SetRotationX(const float x);
	void SetRotationY(const float y);
	void SetRotationZ(const float z);
};

