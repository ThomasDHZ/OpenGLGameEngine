#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <list>
#include <glm/glm.hpp>

class GLWindow
{
private:
	unsigned int OpenGLVersionMajor;
	unsigned int OpenGLVersionMinor;
	int Width = 0;
	int Height = 0;

	GLFWwindow* Window;
	glm::vec3 BackGroundColor;

public:
	GLWindow();
	GLWindow(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName);
	~GLWindow();

	void BufferSize();
	void StartFrame();
	void EndFrame();
	void SetBackGroundColor(float red, float green, float blue);
	void SetBackGroundColor(glm::vec3 color);
	void ShutDownGLWindow();

	GLFWwindow* GetWindow() { return Window; }
	int GetWindowWidth() { return Width; }
	int GetWindowHeight() { return Height; }
};

