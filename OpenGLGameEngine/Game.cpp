#include "Game.h"

Game::Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName)
{
	std::vector<Vertex> vertices =
	{
		{ glm::vec3{0.5f,  .5f, 0.0f} },
		{ glm::vec3{0.5f, -.5f, 0.0f} },
		{ glm::vec3{-.5f, -.5f, 0.0f} },
		{ glm::vec3{-.5f,  .5f, 0.0f} }
	};

	std::vector<unsigned int> indices =
	{
		0, 1, 3,
		1, 2, 3
	};

	Window = GLWindow{ 4, 6, 3840, 2160, "GameWindow" };
	Window.SetBackGroundColor(glm::vec3{ 1.0f, 0.0f, 0.0f });

	GraphicsManager.CompileVertexShader("Shader.vs");
	GraphicsManager.CompileFragmentShader("Shader.fs");
	GraphicsManager.BindShaderProgram(GraphicsManager.GetVertexShader(), GraphicsManager.GetFragmentShader());

	mesh = Mesh(vertices, indices, GraphicsManager);
}

Game::~Game()
{
	mesh.DeleteBuffers();
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
}

void Game::ProcessMouse(double xpos, double ypos)
{
	if (glfwGetMouseButton(Window.GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (FirstMouse)
		{
			LastX = xpos;
			LastY = ypos;
			FirstMouse = false;
		}

		float xoffset = xpos - LastX;
		float yoffset = LastY - ypos;

		LastX = xpos;
		LastY = ypos;
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

	glfwGetCursorPos(Window.GetWindow(), &MouseXPos, &MouseYPos);

	Window.StartFrame();
	ProcessInput();
	ProcessMouse(MouseXPos, MouseYPos);
	Update();
	Window.EndFrame();
}

void Game::Update()
{
	GraphicsManager.UseShaderProgram(GraphicsManager.GetShaderProgram());
	mesh.Update(GraphicsManager);
}


