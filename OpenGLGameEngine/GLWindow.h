#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <list>
#include <glm/glm.hpp>

class GLWindow
{
private:
	//Camera camera;
	unsigned int OpenGLVersionMajor;
	unsigned int OpenGLVersionMinor;
	int Width = 0;
	int Height = 0;
	glm::mat4 Projection;
	glm::mat4 View;

	GLFWwindow* Window;
	glm::vec3 BackGroundColor = glm::vec3(0.0f);


public:
	GLWindow();
	GLWindow(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, const char* WindowName);
	~GLWindow();
	GLFWwindow* GetWindow() { return Window; }

	void BufferSize();
	void StartFrame();
	void EndFrame();
	void SetBackGroundColor(float red, float green, float blue);
	void SetBackGroundColor(glm::vec3 color);
	void ShutDownGLWindow();

	//Camera GetCamera() { return camera; }
	//unsigned int GetWindowWidth() { return width; }
	//unsigned int GetWindowHeight() { return height; }
	//glm::mat4 GetProjection() { return projection; }
	//glm::mat4 GetView() { return view; }
};

