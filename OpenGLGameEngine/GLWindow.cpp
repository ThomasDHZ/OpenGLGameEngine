#include "GLWindow.h"
#include <iostream>

GLWindow::GLWindow()
{
}

GLWindow::~GLWindow()
{
	glfwTerminate();
	Window = nullptr;
}

GLWindow::GLWindow(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, std::string WindowName)
{
	Width = width;
	Height = height;

	OpenGLVersionMajor = openGLVersionMajor;
	OpenGLVersionMinor = openGLVersionMinor;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window = glfwCreateWindow(Width, Height, "LearnOpenGL", NULL, NULL);
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

	//camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

void GLWindow::ProcessInput()
{
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Window, true);

	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	camera.ProcessKeyboard(FORWARD, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	camera.ProcessKeyboard(BACKWARD, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	camera.ProcessKeyboard(LEFT, deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	camera.ProcessKeyboard(RIGHT, deltaTime);
}

void GLWindow::ProcessMouse(double xpos, double ypos)
{
	if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
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

		//camera.ProcessMouseMovement(xoffset, yoffset);
	}
	else
	{
		FirstMouse = true;
	}
}

void GLWindow::BufferSize()
{
	glViewport(0, 0, Width, Height);
}

void GLWindow::Update()
{
	float currentFrame = glfwGetTime();
	DeltaTime = currentFrame - LastFrame;
	LastFrame = currentFrame;

	ProcessInput();

	glfwGetCursorPos(Window, &MouseXPos, &MouseYPos);
	ProcessMouse(MouseXPos, MouseYPos);

	glfwGetFramebufferSize(Window, &Width, &Height);
	BufferSize();

	glClearColor(BackGroundColor.r, BackGroundColor.g, BackGroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
	//view = camera.GetViewMatrix();
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

