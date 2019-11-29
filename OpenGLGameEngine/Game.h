#pragma once
#include "GLManager.h"
#include "GLWindow.h"
#include "Mesh.h"

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

	GLManager GraphicsManager;
	GLWindow Window;
	Mesh mesh;
public:
	Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName);
	~Game();
	void ProcessInput();
	void ProcessMouse(double xpos, double ypos);
	void MainLoop();
	void Update();

	GLFWwindow* GetWindow() { return Window.GetWindow(); }
};

