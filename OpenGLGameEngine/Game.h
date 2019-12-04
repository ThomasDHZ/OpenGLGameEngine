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
	unsigned int SCR_WIDTH;
	unsigned int SCR_HEIGHT;
	float LastX;
	float LastY;
	float DeltaTime;
	float LastFrame;
	double MouseXPos;
	double MouseYPos;
	bool FirstMouse;

	GLWindow Window;
	Camera camera;
	FrameBuffer fBuffer;

	Shader2 shader;
	Shader2 screenShader;
	Mesh cube;
	Mesh plane;
	Texture cubeTexture;
	Texture floorTexture;

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

