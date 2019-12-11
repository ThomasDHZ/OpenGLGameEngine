#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"
#include "camera.h"
#include <FileSystem.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
#include "shader_m.h"
#include "GLWindow.h"
#include "Texture.h"
#include "Vertex.h"
#include "Mesh.h"
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
	GLWindow Window = GLWindow{ 4, 6, 800, 600, "GameWindow" };
	Window.SetBackGroundColor(glm::vec3{ 0.0f, 0.1f, 0.2f });

	glfwMakeContextCurrent(Window.GetWindow());
	glfwSetFramebufferSizeCallback(Window.GetWindow(), framebuffer_size_callback);
	glfwSetCursorPosCallback(Window.GetWindow(), mouse_callback);
	glfwSetScrollCallback(Window.GetWindow(), scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(Window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader2 lightingShader("Shader.vs", "Shader.fs");
	Shader2 lampShader("LampShader.vs", "LampShader.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	std::vector<Vertex> vertices =
	{
		{glm::vec3{-0.5f, -0.5f, -0.5f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{ 0.0f, 0.0f}},
		{glm::vec3{0.5f, -0.5f, -0.5f},   glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{  1.0f, 0.0f}},
		{glm::vec3{0.5f,  0.5f, -0.5f},   glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{0.5f,  0.5f, -0.5f},   glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{-0.5f,  0.5f, -0.5f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{-0.5f, -0.5f, -0.5f},  glm::vec3{0.0f,  0.0f, -1.0f},  glm::vec2{  0.0f, 0.0f}},

		{glm::vec3{-0.5f, -0.5f,  0.5f},  glm::vec3{0.0f,  0.0f,  1.0f},  glm::vec2{  0.0f, 0.0f}},
		{glm::vec3{ 0.5f, -0.5f,  0.5f},  glm::vec3{0.0f,  0.0f,  1.0f},  glm::vec2{  1.0f, 0.0f}},
		{glm::vec3{ 0.5f,  0.5f,  0.5f},  glm::vec3{0.0f,  0.0f,  1.0f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{ 0.5f,  0.5f,  0.5f},  glm::vec3{0.0f,  0.0f,  1.0f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{-0.5f,  0.5f,  0.5f},  glm::vec3{0.0f,  0.0f,  1.0f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{-0.5f, -0.5f,  0.5f},  glm::vec3{0.0f,  0.0f,  1.0f},  glm::vec2{  0.0f, 0.0f}},

		{glm::vec3{-0.5f,  0.5f,  0.5f},  glm::vec3{-1.0f,  0.0f,  0.0f}, glm::vec2{ 1.0f, 0.0f}},
		{glm::vec3{-0.5f,  0.5f, -0.5f},  glm::vec3{-1.0f,  0.0f,  0.0f}, glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{-0.5f, -0.5f, -0.5f},  glm::vec3{-1.0f,  0.0f,  0.0f}, glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{	-0.5f, -0.5f, -0.5f}, glm::vec3{-1.0f,  0.0f,  0.0f}, glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{-0.5f, -0.5f,  0.5f},  glm::vec3{-1.0f,  0.0f,  0.0f}, glm::vec2{  0.0f, 0.0f}},
		{glm::vec3{	-0.5f,  0.5f,  0.5f}, glm::vec3{-1.0f,  0.0f,  0.0f}, glm::vec2{  1.0f, 0.0f}},

		{glm::vec3{ 0.5f,  0.5f,  0.5f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{ 1.0f, 0.0f}},
		{glm::vec3{ 0.5f,  0.5f, -0.5f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{ 0.5f, -0.5f, -0.5f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{ 0.5f, -0.5f, -0.5f},  glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{	 0.5f, -0.5f,  0.5f}, glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{ 0.0f, 0.0f}},
		{glm::vec3{	 0.5f,  0.5f,  0.5f}, glm::vec3{1.0f,  0.0f,  0.0f},  glm::vec2{ 1.0f, 0.0f}},

		{glm::vec3{	-0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{	 0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{	 0.5f, -0.5f,  0.5f}, glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{  1.0f, 0.0f}},
		{glm::vec3{ 0.5f, -0.5f,  0.5f},  glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{  1.0f, 0.0f}},
		{glm::vec3{	-0.5f, -0.5f,  0.5f}, glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{  0.0f, 0.0f}},
		{glm::vec3{	-0.5f, -0.5f, -0.5f}, glm::vec3{0.0f, -1.0f,  0.0f},  glm::vec2{  0.0f, 1.0f}},

		{glm::vec3{	-0.5f,  0.5f, -0.5f}, glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{  0.0f, 1.0f}},
		{glm::vec3{	 0.5f,  0.5f, -0.5f}, glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{  1.0f, 1.0f}},
		{glm::vec3{	 0.5f,  0.5f,  0.5f}, glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{  1.0f, 0.0f}},
		{glm::vec3{	 0.5f,  0.5f,  0.5f}, glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{  1.0f, 0.0f}},
		{glm::vec3{	-0.5f,  0.5f,  0.5f}, glm::vec3{0.0f,  1.0f,  0.0f},  glm::vec2{ 0.0f, 0.0f}},
		{glm::vec3{	-0.5f,  0.5f, -0.5f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{0.0f, 1.0f}}
	};
	float vertices2[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	// positions all containers
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
	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	std::vector<unsigned int> indices = { };

	Mesh boxes = Mesh(vertices, indices);
	Mesh lightbox = Mesh(vertices, indices);
	lightbox.SetScale(glm::vec3(0.2f));

	// load textures (we now use a utility function to keep the code more organized)
	// -----------------------------------------------------------------------------
	Texture diffuseMap = Texture("Assets/container2.png");
	Texture specularMap = Texture("Assets/container2_specular.png");

	// shader configuration
	// --------------------
	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(Window.GetWindow()))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Window.StartFrame();
		processInput(Window.GetWindow());


		lightingShader.use();
		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setFloat("material.shininess", 32.0f);

		lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[0].constant", 1.0f);
		lightingShader.setFloat("pointLights[0].linear", 0.09);
		lightingShader.setFloat("pointLights[0].quadratic", 0.032);

		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[1].constant", 1.0f);
		lightingShader.setFloat("pointLights[1].linear", 0.09);
		lightingShader.setFloat("pointLights[1].quadratic", 0.032);

		lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
		lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[2].constant", 1.0f);
		lightingShader.setFloat("pointLights[2].linear", 0.09);
		lightingShader.setFloat("pointLights[2].quadratic", 0.032);

		lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
		lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("pointLights[3].constant", 1.0f);
		lightingShader.setFloat("pointLights[3].linear", 0.09);
		lightingShader.setFloat("pointLights[3].quadratic", 0.032);

		lightingShader.setVec3("spotLight.position", camera.Position);
		lightingShader.setVec3("spotLight.direction", camera.Front);
		lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		lightingShader.setFloat("spotLight.constant", 1.0f);
		lightingShader.setFloat("spotLight.linear", 0.09);
		lightingShader.setFloat("spotLight.quadratic", 0.032);
		lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		lightingShader.setMat4("projection", projection);
		lightingShader.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		lightingShader.setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap.GetTextureID());

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap.GetTextureID());


		for (unsigned int i = 0; i < 10; i++)
		{
			boxes.SetPosition(cubePositions[i]);
			boxes.SetRotation(glm::vec3(1.0f, 0.3f, 0.5f));
			boxes.Update(diffuseMap.GetTextureID(), specularMap.GetTextureID(), lightingShader);
		}

		// also draw the lamp object(s)
		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);


		for (unsigned int i = 0; i < 4; i++)
		{
			boxes.SetPosition(pointLightPositions[i]);
			boxes.Update(diffuseMap.GetTextureID(), specularMap.GetTextureID(), lampShader);
		}


		Window.EndFrame();
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

