#pragma once
#include <glad/glad.h>
#include <cstddef>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "Layer2D.h"

class Display2D
{
private:

	enum DisplayVertexMap
	{
		Position,
		TextureCoord
	};

	struct DisplayVertex
	{
		glm::vec2 Position = glm::vec2(0.0f);
		glm::vec2 TextureCoord = glm::vec2(0.0f);
	};

	std::vector<DisplayVertex> DisplayVertices =
	{
		{ glm::vec2{-1.0f,  1.0f}, glm::vec2{0.0f, 1.0f} },
		{ glm::vec2{-1.0f, -1.0f}, glm::vec2{0.0f, 0.0f} },
		{ glm::vec2{ 1.0f, -1.0f}, glm::vec2{1.0f, 0.0f} },

		{ glm::vec2{-1.0f,  1.0f}, glm::vec2{0.0f, 1.0f} },
		{ glm::vec2{ 1.0f, -1.0f}, glm::vec2{1.0f, 0.0f} },
		{ glm::vec2{ 1.0f,  1.0f}, glm::vec2{1.0f, 1.0f} }
	};

	unsigned int FrameBufferID;
	unsigned int FrameBufferVAO;
	unsigned int FrameBufferVBO;
	unsigned int FrameBufferRBO;
	unsigned int VertexCount;
	unsigned int Width;
	unsigned int Height;

public:
	Display2D();
	Display2D(unsigned int width, unsigned int height);
	~Display2D();

	void InitializeFrameBuffer();
	void Update(unsigned int TextureID, std::vector<Layer2D>& LayerList);
	void CloseFrameBuffer();
	Display2D& operator=(const Display2D& rhs);
};

