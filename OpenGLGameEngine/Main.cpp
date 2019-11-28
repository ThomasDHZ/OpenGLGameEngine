
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "GLWindow.h"
#include "Mesh.h"
#include "GLManager.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	using namespace glm;

	GLManager glManager = GLManager();

	GLWindow window = { 4, 6, 800, 800, "GameWindow" };

	glManager.CompileVertexShader("Shader.vs");
	glManager.CompileFragmentShader("Shader.fs");
	glManager.BindShaderProgram(glManager.GetVertexShader(), glManager.GetFragmentShader());

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	std::vector<Vertex> vertices2 =
	{
		{ vec3{0.5f,  .5f, 0.0f} },
		{ vec3{0.5f, -.5f, 0.0f} },
		{ vec3{-.5f, -.5f, 0.0f} },
		{ vec3{-.5f,  .5f, 0.0f} }
	};


	std::vector<unsigned int> indices2 =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	Mesh mesh = Mesh(vertices2, indices2, glManager);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		window.Update();
		processInput(window.GetWindow());

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glManager.UseShaderProgram(glManager.GetShaderProgram());
		mesh.Update(glManager);

		window.EndFrame();
	}

	mesh.DeleteBuffers();

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
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


































