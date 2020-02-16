#pragma once
#include "../OpenGL.Base/GLWindow.h"
#include "../OpenGL.Graphics3D/Mesh.h"
#include "../OpenGL.Graphics3D/Texture.h"
#include "../OpenGL.Graphics3D/FrameBuffer.h"
#include "../OpenGL.Graphics3D/camera.h"
#include "GameMode.h"
#include "../OpenGL.Graphics3D/DirectionalLight.h"
#include "../OpenGL.Graphics3D/PointLight.h"
#include "../OpenGL.Graphics2D/Display2D.h"
#include "../OpenGL.Graphics2D/BackGroundLayer.h"
#include "../OpenGL.Graphics2D/Layer2D.h"
#include "../OpenGL.Graphics2D/DisplayManager2D.h"
#include "SkyBox.h"
#include "Model.h"

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
	int SpriteOffsetX;
	int SpriteOffsetY;

	GLWindow Window;
	Camera camera;

	Shader2 shader;
	Shader2 lampShader;
	Shader2 screenShader;
	Shader2 SkyBoxShader;

	EngineMesh cube;
	EngineMesh LightMesh;
	EngineMesh plane;
	EngineMesh Windows;
	EngineMesh Floor;
	Model NewModel;

	SkyBox skybox;

	std::shared_ptr<Texture> DQ1MapTexture;
	Texture cubeTexture;
	Texture floorTexture;
	Texture grassTexture;
	std::shared_ptr<Sprite> windowTexture;
	Texture containerTexture;
	Texture diffuseMap;
	Texture specularMap;
	Texture reflectionMap;
	Texture textureFrame;
	Texture textureFrame2;
	Texture BlankTexture;
	Texture FloorTexture;

	DirectionalLight Dlight;
	PointLight PLight1;
	PointLight PLight2;
	PointLight PLight3;
	PointLight PLight4;

	GameMode GameType;

	FrameBuffer fBuffer;
	//BackGroundLayer backgroundLayer;
	//Layer2D layer;

	DisplayManager2D DManger2D;

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
