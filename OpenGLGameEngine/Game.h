#pragma once
#include "GLGraphicsManager.h"
#include "GLWindow.h"
#include "Mesh.h"
#include "Texture.h"

class Game
{
private:
	float LastX = 1000 / 2.0f;
	float LastY = 1000 / 2.0f;
	double MouseXPos;
	double MouseYPos;
	bool FirstMouse = true;

	GLGraphicsManager GraphicsManager;
	GLWindow Window;
	Mesh mesh;
	Texture texture;
	Texture texture2;
	Texture texture3;
	glm::vec3 cubePositions[10];

	glm::mat4 WorldView = glm::mat4(1.0f);
	glm::mat4 WorldProjection = glm::mat4(1.0f);

public:
	Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName);
	~Game();
	void ProcessInput();
	void ProcessMouse();
	void MainLoop();
	void Update();

	GLFWwindow* GetWindow() { return Window.GetWindow(); }
};

