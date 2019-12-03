#include "Game.h"
#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"
#include <FileSystem.h>
#include <glm\ext\matrix_transform.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include "shader_m.h"

Game::Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName)
{
std::vector<Vertex> vertices =
{
	{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},
	 {glm::vec3{0.5f, -0.5f, -0.5f}, glm::vec2{1.0f, 0.0f}},
	 {glm::vec3{0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
	 {glm::vec3{0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
	{glm::vec3{-0.5f,  0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
	{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 0.0f}},

	{glm::vec3{-0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
	 {glm::vec3{0.5f, -0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
	 {glm::vec3{0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 1.0f}},
	 {glm::vec3{0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 1.0f}},
	{glm::vec3{-0.5f,  0.5f,  0.5f}, glm::vec2{0.0f, 1.0f}},
	{glm::vec3{-0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},

	{glm::vec3{-0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
	{glm::vec3{-0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
	{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
	{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f} },
	{glm::vec3{-0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
	{glm::vec3{-0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},

	{glm::vec3{0.5f,  0.5f,  0.5f},   glm::vec2{1.0f, 0.0f}},
	{glm::vec3{0.5f,  0.5f, -0.5f},  glm::vec2{1.0f, 1.0f}},
	{glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{0.0f, 1.0f}},
	{glm::vec3{0.5f, -0.5f, -0.5f},  glm::vec2{0.0f, 1.0f}},
	{glm::vec3{ 0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
	{glm::vec3{ 0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},

	{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
	{glm::vec3{ 0.5f, -0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
	{glm::vec3{0.5f, -0.5f,  0.5f},  glm::vec2{1.0f, 0.0f}},
	{glm::vec3{0.5f, -0.5f,  0.5f},  glm::vec2{1.0f, 0.0f}},
	{glm::vec3{-0.5f, -0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
	{glm::vec3{-0.5f, -0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},

	{glm::vec3{-0.5f,  0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}},
	{glm::vec3{ 0.5f,  0.5f, -0.5f}, glm::vec2{1.0f, 1.0f}},
	{glm::vec3{ 0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
	{glm::vec3{ 0.5f,  0.5f,  0.5f}, glm::vec2{1.0f, 0.0f}},
	{glm::vec3{-0.5f,  0.5f,  0.5f}, glm::vec2{0.0f, 0.0f}},
	{glm::vec3{-0.5f,  0.5f, -0.5f}, glm::vec2{0.0f, 1.0f}}
};

	std::vector<unsigned int> indices = { };

	cubePositions[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	cubePositions[1] = glm::vec3(2.0f, 5.0f, -15.0f);
	cubePositions[2] = glm::vec3(-1.5f, -2.2f, -2.5f);
	cubePositions[3] = glm::vec3(-3.8f, -2.0f, -12.3f);
	cubePositions[4] = glm::vec3(2.4f, -0.4f, -3.5f);
	cubePositions[5] = glm::vec3(-1.7f, 3.0f, -7.5f);
	cubePositions[6] = glm::vec3(1.3f, -2.0f, -2.5f);
	cubePositions[7] = glm::vec3(1.5f, 2.0f, -2.5f);
	cubePositions[8] = glm::vec3(1.5f, 0.2f, -1.5f);
	cubePositions[9] = glm::vec3(-1.3f, 1.0f, -1.5f);

	Window = GLWindow{ 4, 6, 3840, 2160, "GameWindow" };
	Window.SetBackGroundColor(glm::vec3{ 0.0f, 0.1f, 0.2f });


	Shader2 shader("Shader.vs", "Shader.fs");
	Shader2 screenShader("FrameBufferShader.vs", "FrameBufferShader.fs");

	GraphicsManager.CompileVertexShader("Shader.vs");
	GraphicsManager.CompileFragmentShader("Shader.fs");

	GraphicsManager.BindShaderProgram(GraphicsManager.GetVertexShader(), GraphicsManager.GetFragmentShader());
	GraphicsManager.AddTexture(Texture("Assets/container.jpg"));
	GraphicsManager.AddTexture(Texture("Assets/alefgardfull4KTest.bmp"));
	GraphicsManager.AddTexture(Texture(3840, 2160));

	mesh = Mesh(vertices, indices, GraphicsManager);
	mesh.SetTextureID(GraphicsManager.GetTexture(1).GetTextureID());

	//glCopyImageSubData(GraphicsManager.GetTexture(1).GetTextureID(), GL_TEXTURE_2D, 0, 3840, 2160, 0, GraphicsManager.GetTexture(2).GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, 3840, 2160, 1);

	WorldProjection = glm::perspective(glm::radians(45.0f), (float)Window.GetWindowWidth() / (float)Window.GetWindowHeight(), 0.1f, 100.0f);
	WorldView = glm::translate(WorldView, glm::vec3(0.0f, 0.0f, -3.0f));

	GraphicsManager.UseShaderProgram(shader.ID);
	GraphicsManager.GetMainShader()->SetShaderProjectionValue(WorldProjection);
	GraphicsManager.GetMainShader()->SetShaderViewnValue(WorldView);

	//GraphicsManager.CompileVertexShader("FrameBufferShader.vs");
	//GraphicsManager.CompileFragmentShader("FrameBufferShader.fs");
	//GraphicsManager.BindShaderProgram(GraphicsManager.GetVertexShader(), GraphicsManager.GetFragmentShader());
	//GraphicsManager.UseShaderProgram(GraphicsManager.GetFrameBufferShader()->GetShaderID());

	fBuffer.InitializeFrameBuffer();
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
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_4) == GLFW_PRESS)
		mesh.SetTextureID(GraphicsManager.GetTexture(0).GetTextureID());
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_5) == GLFW_PRESS)
		mesh.SetTextureID(GraphicsManager.GetTexture(1).GetTextureID());
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_6) == GLFW_PRESS)
		mesh.SetTextureID(GraphicsManager.GetTexture(2).GetTextureID());
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

void Game::MainLoop()
{
	float currentFrame = glfwGetTime();
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;

	Window.StartFrame();
	ProcessInput();
	ProcessMouse();
	fBuffer.FrameBufferStart();
	Update();
	//fBuffer.FrameBufferEnd();
	Window.EndFrame();
}

void Game::Update()
{
	

	for (unsigned int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		GraphicsManager.GetMainShader()->SetShaderModelValue(model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	//mesh.Update(GraphicsManager);

}


