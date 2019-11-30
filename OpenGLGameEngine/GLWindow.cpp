#include "GLWindow.h"
#include <iostream>
#include <GL/gl.h>

GLWindow::GLWindow()
{
}

GLWindow::~GLWindow()
{

}

GLWindow::GLWindow(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName)
{
	Width = width;
	Height = height;

	OpenGLVersionMajor = openGLVersionMajor;
	OpenGLVersionMinor = openGLVersionMinor;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window = glfwCreateWindow(Width, Height, WindowName, NULL, NULL);
	if (Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);
}

void GLWindow::BufferSize()
{
	glViewport(0, 0, Width, Height);
}

void GLWindow::StartFrame()
{
	glfwGetFramebufferSize(Window, &Width, &Height);
	BufferSize();

	glClearColor(BackGroundColor.r, BackGroundColor.g, BackGroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void GLWindow::EndFrame()
{
	glfwSwapBuffers(Window);
	glfwPollEvents();
}

void GLWindow::SetBackGroundColor(float red, float green, float blue)
{
	BackGroundColor = glm::vec3(red, green, blue);
}

void GLWindow::SetBackGroundColor(glm::vec3 color)
{
	BackGroundColor = color;
}

void GLWindow::ShutDownGLWindow()
{
	glfwTerminate();
	Window = nullptr;
}

