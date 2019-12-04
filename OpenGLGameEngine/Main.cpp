

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"
#include "camera.h"

#include <iostream>
#include <FileSystem.h>
#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"
#include "FrameBuffer.h"
#include "Texture.h"
#include "GLWindow.h"
#include "Vertex.h"
#include "Mesh.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

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

int main()
{
	GLWindow Window = GLWindow{ 4, 6, SCR_WIDTH, SCR_HEIGHT, "GameWindow" };
	Window.SetBackGroundColor(glm::vec3{ 0.0f, 0.1f, 0.2f });

	glfwSetCursorPosCallback(Window.GetWindow(), mouse_callback);
	glfwSetScrollCallback(Window.GetWindow(), scroll_callback);
	glfwSetInputMode(Window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	Shader2 shader("5.1.framebuffers.vs", "5.1.framebuffers.fs");
	Shader2 screenShader("FrameBufferShader.vs", "FrameBufferShader.fs");

	std::vector<unsigned int> indices = { };

	Mesh cube = Mesh(vertices, indices);
	Mesh plane = Mesh(plainVert, indices);

	Texture cubeTexture = Texture("Assets/alefgardfull4KTest.bmp");
	Texture floorTexture = Texture("Assets/metal.png");

	shader.use();
	shader.setInt("texture1", 0);

	screenShader.use();
	screenShader.setInt("screenTexture", 0);

	FrameBuffer fBuffer = FrameBuffer(); 
	fBuffer.InitializeFrameBuffer();

	while (!glfwWindowShouldClose(Window.GetWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(Window.GetWindow());


		fBuffer.FrameBufferStart();

		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		for (int x = 0; x < 10; x++)
		{
			cube.SetPosition(cubePositions[x]);
			cube.SetRotation(glm::vec3(20.0f * x));
			cube.Update(cubeTexture.GetTextureID(), model, shader);
		}

		//glm::mat4 model2 = glm::mat4(1.0f);
		//plane.SetModelMatrix(model2);
		//plane.Update(floorTexture.GetTextureID(), model2, shader);

	

		screenShader.use();
		fBuffer.FrameBufferEnd();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(Window.GetWindow());
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}



//
//
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include "shader_s.h"
//#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"
//#include <FileSystem.h>
//#include "GLWindow.h"
//#include "Mesh.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 3840;
//const unsigned int SCR_HEIGHT = 2160;
//int offsetX = 0;
//int offsetY = 0;
//int main()
//{
//	using namespace glm;
//
//	GLWindow window = { 4, 6, 3840, 2160, "GameWindow" };
//
//	// build and compile our shader zprogram
//	// ------------------------------------
//	Shader ourShader("4.2.texture.vs", "4.2.texture.fs");
//
//	// set up vertex data (and buffer(s)) and configure vertex attributes
//	// ------------------------------------------------------------------
//	float vertices[] = {
//		// positions          // colors           // texture coords
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//		 0.5f, -.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//		-.5f, -.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//		-.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
//	};
//
//	unsigned int indices[] = {
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//
//	std::vector<Vertex> vertices2 =
//	{
//		{ vec3{0.5f,  .5f, 0.0f},   vec3{1.0f, 0.0f, 0.0f},   vec2{1.0f, 1.0f} },
//		{ vec3{0.5f, -.5f, 0.0f},   vec3{0.0f, 1.0f, 0.0f},   vec2{1.0f, 0.0f} },
//		{ vec3{-.5f, -.5f, 0.0f},   vec3{0.0f, 0.0f, 1.0f},   vec2{0.0f, 0.0f} },
//		{ vec3{-.5f,  .5f, 0.0f},   vec3{1.0f, 1.0f, 0.0f},   vec2{0.0f, 1.0f} }
//	};
//
//
//	std::vector<unsigned int> indices2 =
//	{
//		0, 1, 3, // first triangle
//		1, 2, 3  // second triangle
//	};
//
//	Mesh mesh = Mesh(vertices2, indices2);
//
//
//	//// load and create a texture 
//	//// -------------------------
//	//unsigned int texture1, texture2;
//	//// texture 1
//	//// ---------
//	//glGenTextures(1, &texture1);
//	//glBindTexture(GL_TEXTURE_2D, texture1);
//	//// set the texture wrapping parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//// set texture filtering parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//// load image, create texture and generate mipmaps
//	//int width, height, nrChannels;
//	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//	//// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
//	//unsigned char* data = stbi_load(FileSystem::getPath("Assets/alefgardfull4KTest.bmp").c_str(), &width, &height, &nrChannels, 0);
//	//if (data)
//	//{
//	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	//	glGenerateMipmap(GL_TEXTURE_2D);
//	//}
//	//else
//	//{
//	//	std::cout << "Failed to load texture" << std::endl;
//	//}
//	//stbi_image_free(data);
//	//// texture 2
//	//// ---------
//	//glGenTextures(1, &texture2);
//	//glBindTexture(GL_TEXTURE_2D, texture2);
//	//// set the texture wrapping parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//// set texture filtering parameters
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//// load image, create texture and generate mipmaps
//	//data = stbi_load(FileSystem::getPath("Assets/TestFrame.bmp").c_str(), &width, &height, &nrChannels, 0);
//	//if (data)
//	//{
//	//	// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
//	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	//	glGenerateMipmap(GL_TEXTURE_2D);
//	//}
//	//else
//	//{
//	//	std::cout << "Failed to load texture" << std::endl;
//	//}
//	//stbi_image_free(data);
//
//	//// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//	//// -------------------------------------------------------------------------------------------
//	//ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
//	//// either set it manually like so:
//	//glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
//	//// or set it via the texture class
//	//ourShader.setInt("texture2", 1);
//
//	//glBindTexture(GL_TEXTURE_2D, texture1);
//	//int a;
//	//glGetIntegerv(GL_TEXTURE_BINDING_2D, &a);
//
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window.GetWindow()))
//	{
//		window.Update();
//		processInput(window.GetWindow());
//
//		glCopyImageSubData(texture1, GL_TEXTURE_2D, 0, 3840 - offsetX, 2160 - offsetY, 0, texture2, GL_TEXTURE_2D, 0, 0, 0, 0, 3840, 2160, 1);
//		// bind textures on corresponding texture units
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);
//
//		// render container
//		ourShader.use();
//		mesh.Update();
//
//		window.EndFrame();
//	}
//
//	// optional: de-allocate all resources once they've outlived their purpose:
//	// ------------------------------------------------------------------------
//	mesh.DeleteBuffers();
//
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		offsetY -= 128;
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		offsetY += 128;
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		offsetX += 128;
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		offsetX -= 128;
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//
//
//
//
//
//


































