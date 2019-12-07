#include "Game.h"
#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"
#include <FileSystem.h>
#include <glm\ext\matrix_transform.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include "shader_m.h"
#include "../GLGraphics/testing.h"

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

Game::Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, GameMode gameMode, const char* WindowName)
{
	testing test = testing();
	std::string a = test.GetWords();
	std::vector<Vertex> vertices =
	{
		{glm::vec3{-0.5f, -0.5f, -0.5f},  glm::vec2{ 0.0f, 0.0f}},
		 {glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{  1.0f, 0.0f}},
		 {glm::vec3{0.5f,  0.5f, -0.5f},  glm::vec2{  1.0f, 1.0f}},
		 {glm::vec3{0.5f,  0.5f, -0.5f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{-0.5f,  0.5f, -0.5f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{-0.5f, -0.5f, -0.5f},  glm::vec2{  0.0f, 0.0f}},

		{glm::vec3{-0.5f, -0.5f,  0.5f},  glm::vec2{  0.0f, 0.0f}},
		{glm::vec3{ 0.5f, -0.5f,  0.5f},  glm::vec2{  1.0f, 0.0f}},
		{glm::vec3{ 0.5f,  0.5f,  0.5f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{ 0.5f,  0.5f,  0.5f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{-0.5f,  0.5f,  0.5f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{-0.5f, -0.5f,  0.5f},  glm::vec2{  0.0f, 0.0f}},

		{glm::vec3{-0.5f,  0.5f,  0.5f},  glm::vec2{ 1.0f, 0.0f}},
		{glm::vec3{-0.5f,  0.5f, -0.5f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{-0.5f, -0.5f, -0.5f},  glm::vec2{  0.0f, 1.0f}},
	{glm::vec3{	-0.5f, -0.5f, -0.5f},  glm::vec2{  0.0f, 1.0f}},
	{glm::vec3{-0.5f, -0.5f,  0.5f},  glm::vec2{  0.0f, 0.0f}},
	{glm::vec3{	-0.5f,  0.5f,  0.5f},  glm::vec2{  1.0f, 0.0f}},

		{glm::vec3{ 0.5f,  0.5f,  0.5f},  glm::vec2{ 1.0f, 0.0f}},
		{glm::vec3{ 0.5f,  0.5f, -0.5f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{ 0.5f, -0.5f, -0.5f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{ 0.5f, -0.5f, -0.5f},  glm::vec2{  0.0f, 1.0f}},
	{glm::vec3{	 0.5f, -0.5f,  0.5f},  glm::vec2{ 0.0f, 0.0f}},
	{glm::vec3{	 0.5f,  0.5f,  0.5f},  glm::vec2{ 1.0f, 0.0f}},

	{glm::vec3{	-0.5f, -0.5f, -0.5f},  glm::vec2{  0.0f, 1.0f}},
	{glm::vec3{	 0.5f, -0.5f, -0.5f},  glm::vec2{  1.0f, 1.0f}},
	{glm::vec3{	 0.5f, -0.5f,  0.5f},  glm::vec2{  1.0f, 0.0f}},
		{glm::vec3{ 0.5f, -0.5f,  0.5f},  glm::vec2{  1.0f, 0.0f}},
	{glm::vec3{	-0.5f, -0.5f,  0.5f},  glm::vec2{  0.0f, 0.0f}},
	{glm::vec3{	-0.5f, -0.5f, -0.5f},  glm::vec2{  0.0f, 1.0f}},

	{glm::vec3{	-0.5f,  0.5f, -0.5f},  glm::vec2{  0.0f, 1.0f}},
	{glm::vec3{	 0.5f,  0.5f, -0.5f},  glm::vec2{  1.0f, 1.0f}},
	{glm::vec3{	 0.5f,  0.5f,  0.5f},  glm::vec2{  1.0f, 0.0f}},
	{glm::vec3{	 0.5f,  0.5f,  0.5f},  glm::vec2{  1.0f, 0.0f}},
	{glm::vec3{	-0.5f,  0.5f,  0.5f},  glm::vec2{ 0.0f, 0.0f}},
	{glm::vec3{	-0.5f,  0.5f, -0.5f},  glm::vec2{0.0f, 1.0f}}
	};
	std::vector<Vertex> plainVert = {
		// positions          // texture Coords 
		 {glm::vec3{5.0f, -0.5f,  5.0f},  glm::vec2{  2.0f, 0.0f}},
		{glm::vec3{-5.0f, -0.5f,  5.0f},  glm::vec2{  0.0f, 0.0f}},
		{glm::vec3{-5.0f, -0.5f, -5.0f},  glm::vec2{  0.0f, 2.0f}},

		{glm::vec3{ 5.0f, -0.5f,  5.0f},  glm::vec2{  2.0f, 0.0f}},
		{glm::vec3{-5.0f, -0.5f, -5.0f},  glm::vec2{  0.0f, 2.0f}},
		 {glm::vec3{5.0f, -0.5f, -5.0f},  glm::vec2{  2.0f, 2.0f}}
	};
	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	Window = GLWindow{ 4, 6, width, height, "GameWindow" };
	Window.SetBackGroundColor(glm::vec3{ 0.0f, 0.1f, 0.2f });

	GameType = gameMode;

	LastX = (float)Window.GetWindowWidth() / 2.0;
	LastY = (float)Window.GetWindowHeight() / 2.0;

	MouseXPos = 0;
	MouseYPos = 0;

	DeltaTime = 0.0f;
	LastFrame = 0.0f;

	FirstMouse = true;

	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	shader = Shader2("5.1.framebuffers.vs", "5.1.framebuffers.fs");
	screenShader = Shader2("FrameBufferShader.vs", "FrameBufferShader.fs");

	std::vector<unsigned int> indices = { };

	cube = Mesh(vertices, indices);
	plane = Mesh(plainVert, indices);

	cubeTexture = Texture("Assets/alefgardfull4KTest.bmp");
	floorTexture = Texture("Assets/metal.png");
	textureFrame = Texture(Window.GetWindowWidth(), Window.GetWindowHeight());

	shader.use();
	shader.setInt("texture1", 0);

	screenShader.use();
	screenShader.setInt("screenTexture", 0);

	fBuffer.InitializeFrameBuffer();
	frame.InitializeFrameBuffer();
}

Game::~Game()
{
	//mesh.DeleteBuffers();
	//Window.ShutDownGLWindow();
}

void Game::ProcessInput()
{
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Window.GetWindow(), true);
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_4) == GLFW_PRESS)
		GameType = Mode2D;
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_5) == GLFW_PRESS)
		GameType = Mode3D;

	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, DeltaTime);
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, DeltaTime);
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, DeltaTime);
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, DeltaTime);

	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		OffsetX += 128;
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		OffsetX -= 128;
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		OffsetY += 128;
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		OffsetY -= 128;
}

void Game::ProcessMouse()
{
	if (glfwGetMouseButton(Window.GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwGetCursorPos(Window.GetWindow(), &MouseXPos, &MouseYPos);

		if (FirstMouse)
		{
			LastX = MouseXPos;
			LastY = MouseYPos;
			FirstMouse = false;
		}

		float xoffset = MouseXPos - LastX;
		float yoffset = LastY - MouseYPos;

		LastX = MouseXPos;
		LastY = MouseYPos;
	}
	else
	{
		FirstMouse = true;
	}
}

void Game::UpdateProjectionView()
{
	shader.use();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Window.GetWindowWidth() / (float)Window.GetWindowHeight(), 0.1f, 100.0f);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
}

void Game::MainLoop()
{
	float currentFrame = glfwGetTime();
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;

	ProcessInput();
	ProcessMouse();

	Window.StartFrame();
	if (GameType == GameMode::Mode3D)
	{
		fBuffer.FrameBufferStart();
		UpdateProjectionView();
		Update();
		fBuffer.FrameBufferEnd();
	}
	else
	{
		Update2D();
	}
	Window.EndFrame();
}

void Game::Update()
{
	glCopyImageSubData(cubeTexture.GetTextureID(), GL_TEXTURE_2D, 0, OffsetX, cubeTexture.GetHeight() - textureFrame.GetHeight() + OffsetY, 0, textureFrame.GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, textureFrame.GetWidth(), textureFrame.GetHeight(), 1);
	
	shader.use();
	for (int x = 0; x < 10; x++)
	{
		cube.SetPosition(cubePositions[x]);
		cube.SetRotation(glm::vec3(20.0f * x));
		cube.Update(textureFrame.GetTextureID(), shader);
	}

	screenShader.use();
}

void Game::Update2D()
{
	shader.use();

	int test = cubeTexture.GetHeight() - textureFrame.GetHeight() + OffsetY;
	screenShader.use();
	glCopyImageSubData(cubeTexture.GetTextureID(), GL_TEXTURE_2D, 0, OffsetX, test, 0, textureFrame.GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, textureFrame.GetWidth(), textureFrame.GetHeight(), 1);
	frame.Update(textureFrame.GetTextureID());
}
