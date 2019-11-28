#pragma once
#include "Frame.h"
#include <GLFW\glfw3.h>

class FrameBuffer
{
private:
	int FrameWidth = 0;
	int FrameHeight = 0;
	int OffsetX = 0;
	int OffsetY = 0;
	unsigned int cubeTexture;
	unsigned int FrameTextureId;
	unsigned int quadVAO;
	unsigned int quadVBO;
	Color* data;
	Color* FrameData;
public:
	FrameBuffer();
	//FrameBuffer(Shader screenShader, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT);
	~FrameBuffer();

	void Update(GLFWwindow* window);
	//void Render(Shader screenShader);
	unsigned int loadTexture(char const* path);

	Color GetMapPixel(int x, int y);
	Color GetPixel(int x, int y);
	void SetPixel(int x, int y, Color color);

	FrameBuffer& operator=(const FrameBuffer& rhs);
};