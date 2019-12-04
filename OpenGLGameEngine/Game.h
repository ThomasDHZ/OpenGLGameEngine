#pragma once
#include "GLGraphicsManager.h"
#include "GLWindow.h"
#include "Mesh.h"
#include "Texture.h"
#include "FrameBuffer.h"
#include "camera.h"

class Game
{
private:
	GLWindow Window;

public:
	Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName);
	~Game();
	void ProcessInput();
	void ProcessMouse();
	void UpdateProjectionView();
	void MainLoop();
	void Update();

	GLFWwindow* GetWindow() { return Window.GetWindow(); }
};

