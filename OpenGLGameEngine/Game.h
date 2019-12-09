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
	float lastX;
	float lastY;
	bool firstMouse;

	float deltaTime;
	float lastFrame;

	double MouseXPos;
	double MouseYPos;

	int OffsetX;
	int OffsetY;

	GLWindow Window;
	Camera camera;

	Shader2 shader;
	Shader2 lampShader;
	Shader2 screenShader;

	Mesh cube;
	Mesh LightMesh;
	Mesh plane;
	Mesh Windows;

	Texture DQ1MapTexture;
	Texture cubeTexture;
	Texture floorTexture;
	Texture grassTexture;
	Texture windowTexture;
	Texture containerTexture;
	Texture textureFrame;

	GameMode GameType;

	Frame frame;
	FrameBuffer fBuffer;

public:
	Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, GameMode gameMode, const char* WindowName);
	~Game();

	void MainLoop();
	void UpdateProjectionView();
	void Update();
	void Update2D();
	void ProcessMouse();
	void ProcessInput();

	GLFWwindow* GetWindow() { return Window.GetWindow(); }
};
