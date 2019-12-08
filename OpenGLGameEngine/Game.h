#pragma once
#include "GLGraphicsManager.h"
#include "GLWindow.h"
#include "Mesh.h"
#include "Texture.h"
#include "FrameBuffer.h"
#include "camera.h"
#include "Frame.h"
#include "GameMode.h"

class Game
{
private:
	float LastX;
	float LastY;
	float DeltaTime;
	float LastFrame;
	double MouseXPos;
	double MouseYPos;
	bool FirstMouse;

	int OffsetX;
	int OffsetY;

	GLWindow Window;
	Camera camera;

	Frame frame;
	FrameBuffer fBuffer;

	Shader2 shader;
	Shader2 screenShader;
	Mesh cube;
	Mesh plane;
	Mesh Windows;
	Texture DQ1MapTexture;
	Texture cubeTexture;
	Texture floorTexture;
	Texture grassTexture;
	Texture windowTexture;
	Texture textureFrame;
	GameMode GameType;
public:
	Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, GameMode gameMode, const char* WindowName);
	~Game();
	void ProcessInput();
	void ProcessMouse();
	void UpdateProjectionView();
	void MainLoop();
	void Update();
	void Update2D();

	GLFWwindow* GetWindow() { return Window.GetWindow(); }
};

