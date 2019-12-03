#pragma once
#include "GLGraphicsManager.h"
#include "GLWindow.h"
#include "Mesh.h"
#include "Texture.h"
#include "FrameBuffer.h"

class Game
{
private:
	float DeltaTime = 0.0f;
	float LastFrame = 0.0f;
	float LastX = 1000 / 2.0f;
	float LastY = 1000 / 2.0f;
	double MouseXPos;
	double MouseYPos;
	bool FirstMouse = true;

	GLGraphicsManager GraphicsManager;
	GLWindow Window;
	Mesh mesh;
	FrameBuffer fBuffer;

	glm::vec3 cubePositions[10];

	glm::mat4 WorldView = glm::mat4(1.0f);
	glm::mat4 WorldProjection = glm::mat4(1.0f);

	unsigned int quadVAO, quadVBO;
	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	unsigned int rbo;

public:
	Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName);
	~Game();
	void ProcessInput();
	void ProcessMouse();
	void MainLoop();
	void Update();

	GLFWwindow* GetWindow() { return Window.GetWindow(); }
};

