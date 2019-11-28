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
	float DeltaTime = 0.0f;
	float LastFrame = 0.0f;
	float LastX = 1000 / 2.0f;
	float LastY = 1000 / 2.0f;
	double MouseXPos;
	double MouseYPos;
	bool FirstMouse = true;
	glm::mat4 Projection;
	glm::mat4 View;

	GLFWwindow* Window;
	glm::vec3 BackGroundColor = glm::vec3(0.0f);


public:
	GLWindow();
	GLWindow(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, std::string WindowName);
	~GLWindow();
	GLFWwindow* GetWindow() { return Window; }

	void ProcessInput();
	void ProcessMouse(double xpos, double ypos);
	void BufferSize();
	void Update();
	void EndFrame();
	void SetBackGroundColor(float red, float green, float blue);
	void SetBackGroundColor(glm::vec3 color);

	//Camera GetCamera() { return camera; }
	//unsigned int GetWindowWidth() { return width; }
	//unsigned int GetWindowHeight() { return height; }
	//glm::mat4 GetProjection() { return projection; }
	//glm::mat4 GetView() { return view; }
};

