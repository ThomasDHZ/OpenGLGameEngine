#include "Game.h"
#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"
#include <FileSystem.h>

Game::Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName)
{
	std::vector<Vertex> vertices =
	{
		{ glm::vec3{0.5f,  .5f, 0.0f}, glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec2(1.0f, 1.0f) },
		{ glm::vec3{0.5f, -.5f, 0.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2(1.0f, 0.0f) },
		{ glm::vec3{-.5f, -.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}, glm::vec2(0.0f, 0.0f) },
		{ glm::vec3{-.5f,  .5f, 0.0f}, glm::vec3{1.0f, 1.0f, 0.0f}, glm::vec2(0.0f, 1.0f) }
	};

	std::vector<unsigned int> indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	Window = GLWindow{ 4, 6, 3840, 2160, "GameWindow" };
	Window.SetBackGroundColor(glm::vec3{ 0.0f, 0.1f, 0.2f });

	GraphicsManager.CompileVertexShader("Shader.vs");
	GraphicsManager.CompileFragmentShader("Shader.fs");
	GraphicsManager.BindShaderProgram(GraphicsManager.GetVertexShader(), GraphicsManager.GetFragmentShader());

	texture = Texture("Assets/container.jpg");
	texture2 = Texture("Assets/alefgardfull4KTest.bmp");

	mesh = Mesh(vertices, indices, GraphicsManager);
	mesh.SetTextureID(texture2.GetTextureID());

	GraphicsManager.UseShaderProgram(GraphicsManager.GetShaderProgram());
	glUniform1i(glGetUniformLocation(GraphicsManager.GetShaderProgram(), "texture1"), 0);
}

Game::~Game()
{
	mesh.DeleteBuffers();
	texture.ReleaseTexture();
	Window.ShutDownGLWindow();
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
		mesh.SetTextureID(texture.GetTextureID());
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_5) == GLFW_PRESS)
		mesh.SetTextureID(texture2.GetTextureID());
}

void Game::ProcessMouse()
{
	glfwGetCursorPos(Window.GetWindow(), &MouseXPos, &MouseYPos);
	if (glfwGetMouseButton(Window.GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
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

void Game::MainLoop()
{
	float currentFrame = glfwGetTime();
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;

	Window.StartFrame();
	ProcessInput();
	ProcessMouse();
	Update();
	Window.EndFrame();
}

void Game::Update()
{
	GraphicsManager.UseShaderProgram(GraphicsManager.GetShaderProgram());
	mesh.Update(GraphicsManager);
}


