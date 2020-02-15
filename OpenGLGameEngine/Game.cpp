#include "Game.h"
#include <map>
#include <Soil\stb_image.h>
#include <FileSystem.h>

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

std::vector<Vertex> plainVert =
{
	 {glm::vec3{5.0f, -0.5f,  5.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{  2.0f, 0.0f}},
	{glm::vec3{-5.0f, -0.5f,  5.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{  0.0f, 0.0f}},
	{glm::vec3{-5.0f, -0.5f, -5.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{  0.0f, 2.0f}},

	{glm::vec3{ 5.0f, -0.5f,  5.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{  2.0f, 0.0f}},
	{glm::vec3{-5.0f, -0.5f, -5.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{  0.0f, 2.0f}},
	 {glm::vec3{5.0f, -0.5f, -5.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{  2.0f, 2.0f}}
};

float quadVertices[] =
{
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
};

std::vector<glm::vec3> windows
{
	glm::vec3(-1.5f, 0.0f, -0.48f),
	glm::vec3(1.5f, 0.0f, 0.51f),
	glm::vec3(0.0f, 0.0f, 0.7f),
	glm::vec3(-0.3f, 0.0f, -2.3f),
	glm::vec3(0.5f, 0.0f, -0.6f)
};

std::vector<Vertex> transparentVertices =
{
	{glm::vec3{0.0f,  0.5f,  0.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{0.0f,  0.0f}},
	{glm::vec3{0.0f, -0.5f,  0.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{0.0f,  1.0f}},
	{glm::vec3{1.0f, -0.5f,  0.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{1.0f,  1.0f}},

	{glm::vec3{0.0f,  0.5f,  0.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{0.0f,  0.0f}},
	{glm::vec3{1.0f, -0.5f,  0.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{1.0f,  1.0f}},
	{glm::vec3{1.0f,  0.5f,  0.0f}, glm::vec3{-0.0f,  1.0f,  0.0f}, glm::vec2{1.0f,  0.0f}}
};

std::vector<Vertex> planeVertices = {
	// positions            // normals         // texcoords
	{glm::vec3{10.0f, -0.5f,  10.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{10.0f,  0.0f}},
	{glm::vec3{-10.0f, -0.5f,  10.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{0.0f,  0.0f}},
	{glm::vec3{-10.0f, -0.5f, -10.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{0.0f, 10.0f}},

	 {glm::vec3{10.0f, -0.5f,  10.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{0.0f,  0.0f}},
	{glm::vec3{-10.0f, -0.5f, -10.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{0.0f, 10.0f}},
	 {glm::vec3{10.0f, -0.5f, -10.0f}, glm::vec3{0.0f, 1.0f, 0.0f}, glm::vec2{10.0f, 10.0f}}
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

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  0.2f,  2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.0f,  2.0f, -12.0f),
	glm::vec3(0.0f,  0.0f, -3.0f)
};

std::vector<unsigned int> indices = { };

glm::vec3 lightPos2(1.2f, 1.0f, 2.0f);

Game::Game(unsigned int openGLVersionMajor, unsigned int openGLVersionMinor, unsigned int width, unsigned int height, GameMode gameMode, const char* WindowName)
{
	lastX = width / 2.0f;
	lastY = height / 2.0f;
	firstMouse = true;

	deltaTime = 0.0f;
	lastFrame = 0.0f;

	MouseXPos = 0.0f;
	MouseYPos = 0.0f;

	OffsetX = 0;
	OffsetY = 0;
	SpriteOffsetX = 0;
	SpriteOffsetY = 0;

	Window = GLWindow{ 4, 6, width, height, "GameWindow" };

	camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	shader = Shader2("Shader.vs", "Shader.fs");
	lampShader = Shader2("LampShader.vs", "LampShader.fs");
	screenShader = Shader2("FrameBufferShader.vs", "FrameBufferShader.fs");
	SkyBoxShader = Shader2("SkyBox.vs", "SkyBox.fs");

	std::vector<unsigned int> indices = { };

	std::vector<std::string> faces
	{
		FileSystem::getPath("Assets/right.jpg"),
		FileSystem::getPath("Assets/left.jpg"),
		FileSystem::getPath("Assets/top.jpg"),
		FileSystem::getPath("Assets/bottom.jpg"),
		FileSystem::getPath("Assets/front.jpg"),
		FileSystem::getPath("Assets/back.jpg"),
	};

	cube = Mesh(vertices, indices);
	LightMesh = Mesh(vertices, indices);
	plane = Mesh(plainVert, indices);
	Windows = Mesh(transparentVertices, indices);
	Floor = Mesh(planeVertices, indices);
	skybox = SkyBox(faces);

	cubeTexture = Texture("Assets/marble.jpg");
	floorTexture = Texture("Assets/metal.png");
	grassTexture = Texture("Assets/cat.png");
	windowTexture = std::make_shared<Sprite>("Assets/window.png", glm::vec2(0.0f, 0.0f));
	containerTexture = Texture("Assets/container.jpg");
	//DQ1MapTexture = std::make_shared<Texture>("Assets/alefgardfull4KTest.bmp");
	diffuseMap = Texture("Assets/container2.png");
	specularMap = Texture("Assets/container2_specular.png");
	textureFrame = Texture(Window.GetWindowWidth(), Window.GetWindowHeight());
	textureFrame2 = Texture(Window.GetWindowWidth(), Window.GetWindowHeight());
	BlankTexture = Texture(Window.GetWindowWidth(), Window.GetWindowHeight());
	FloorTexture = Texture("Assets/wood.png");

	Dlight = DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f));
	PLight1 = PointLight(pointLightPositions[0], 0);
	PLight2 = PointLight(pointLightPositions[1], 1);
	PLight3 = PointLight(pointLightPositions[2], 2);
	PLight4 = PointLight(pointLightPositions[3], 3);
	GameType = gameMode;

	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);

	DManger2D = DisplayManager2D(Window.GetWindowWidth(), Window.GetWindowHeight(), 30);
	DManger2D.AddBackGroundImage(DQ1MapTexture);
	DManger2D.AddSprite(windowTexture, 14);

	//fBuffer.InitializeFrameBuffer(width, height);

	screenShader.use();
	for (int x = 0; x <= 31; x++)
	{
		screenShader.setInt("Layer[" + std::to_string(x) + "]", x);
	}

	LightMesh.SetScale(glm::vec3(0.2f));
}

Game::~Game()
{
	cube.DeleteBuffers();
	Window.ShutDownGLWindow();
}

void Game::MainLoop()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	ProcessInput();
	ProcessMouse();

	Window.StartFrame();
	if (GameType == GameMode::Mode3D)
	{
		//fBuffer.FrameBufferStart();
		UpdateProjectionView();
		Update();
		//fBuffer.FrameBufferEnd();
	}
	else
	{
		glCopyImageSubData(BlankTexture.GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, textureFrame2.GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, BlankTexture.GetWidth(), BlankTexture.GetHeight(), 1);
		Update2D();
	}
	Window.EndFrame();
}

void Game::UpdateProjectionView()
{
	shader.use();

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Window.GetWindowWidth() / (float)Window.GetWindowHeight(), 0.1f, 100.0f);
	shader.setMat4("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("view", view);
}

void Game::Update()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader.use();
	shader.setVec3("viewPos", camera.Position);
	shader.setFloat("material.shininess", 32.0f);

	// directional light
	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	// point light 1
	shader.setVec3("pointLights[0].position", pointLightPositions[0]);
	shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
	shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[0].constant", 1.0f);
	shader.setFloat("pointLights[0].linear", 0.09);
	shader.setFloat("pointLights[0].quadratic", 0.032);
	// point light 2
	shader.setVec3("pointLights[1].position", pointLightPositions[1]);
	shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
	shader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[1].constant", 1.0f);
	shader.setFloat("pointLights[1].linear", 0.09);
	shader.setFloat("pointLights[1].quadratic", 0.032);
	// point light 3
	shader.setVec3("pointLights[2].position", pointLightPositions[2]);
	shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
	shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[2].constant", 1.0f);
	shader.setFloat("pointLights[2].linear", 0.09);
	shader.setFloat("pointLights[2].quadratic", 0.032);
	// point light 4
	shader.setVec3("pointLights[3].position", pointLightPositions[3]);
	shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
	shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[3].constant", 1.0f);
	shader.setFloat("pointLights[3].linear", 0.09);
	shader.setFloat("pointLights[3].quadratic", 0.032);
	// spotLight
	shader.setVec3("spotLight.position", camera.Position);
	shader.setVec3("spotLight.direction", camera.Front);
	shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.09);
	shader.setFloat("spotLight.quadratic", 0.032);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Window.GetWindowWidth() / (float)Window.GetWindowHeight(), 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	shader.setMat4("model", model);


	for (unsigned int i = 0; i < 10; i++)
	{
		cube.SetPosition(cubePositions[i]);
		cube.SetRotation(glm::vec3(1.0f, 0.3f, 0.5f));
		cube.Update(diffuseMap.GetTextureID(), specularMap.GetTextureID(), shader);
	}

	Floor.Update(FloorTexture.GetTextureID(), BlankTexture.GetTextureID(), shader);

	// also draw the lamp object(s)
	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);


	for (unsigned int i = 0; i < 4; i++)
	{
		cube.SetPosition(pointLightPositions[i]);
		cube.Update(diffuseMap.GetTextureID(), specularMap.GetTextureID(), lampShader);
	}

	skybox.Update(SkyBoxShader, camera, Window.GetWindowWidth(), Window.GetWindowHeight());



	/*std::map<float, glm::vec3> sorted;
	for (unsigned int i = 0; i < windows.size(); i++)
	{
		float distance = glm::length(camera.Position - windows[i]);
		sorted[distance] = windows[i];
	}

	shader.use();
	shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	shader.setVec3("lightPos", lightPos2);
	shader.setVec3("viewPos", camera.Position);

	cube.SetPosition(glm::vec3(-1.0f, 0.0f, -1.0f));
	cube.Update(cubeTexture.GetTextureID(), shader);

	cube.SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	cube.Update(cubeTexture.GetTextureID(), shader);

	plane.Update(floorTexture.GetTextureID(), shader);

	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		Windows.SetPosition(it->second);
		Windows.Update(windowTexture.GetTextureID(), shader);
	}

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Window.GetWindowWidth() / (float)Window.GetWindowHeight(), 0.1f, 100.0f);
	shader.setMat4("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	shader.setMat4("view", view);

	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);

	LightMesh.SetPosition(lightPos2);
	LightMesh.Update(windowTexture.GetTextureID(), lampShader);*/

	screenShader.use();
}

void Game::Update2D()
{
	shader.use();

	screenShader.use();

	DManger2D.SetBackGroundPosition(OffsetX, OffsetY);
	windowTexture->SetPosition(SpriteOffsetX, SpriteOffsetY);

	DManger2D.Update();
}

void Game::ProcessMouse()
{
	if (glfwGetMouseButton(Window.GetWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwGetCursorPos(Window.GetWindow(), &MouseXPos, &MouseYPos);
		if (firstMouse)
		{
			lastX = MouseXPos;
			lastY = MouseYPos;
			firstMouse = false;
		}

		float xoffset = MouseXPos - lastX;
		float yoffset = lastY - MouseYPos;

		lastX = MouseXPos;
		lastY = MouseYPos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	else
	{
		firstMouse = true;
	}
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
		GameType = Mode2D;
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_5) == GLFW_PRESS)
		GameType = Mode3D;

	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		if (GameType == Mode3D)
		{
			camera.ProcessKeyboard(FORWARD, deltaTime);
		}
		else
		{
			SpriteOffsetY += 128;
		}
	}
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		if (GameType == Mode3D)
		{
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		}
		else
		{
			SpriteOffsetY -= 128;
		}
	}
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		if (GameType == Mode3D)
		{
			camera.ProcessKeyboard(LEFT, deltaTime);
		}
		else
		{
			SpriteOffsetX -= 128;
		}
	}
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		if (GameType == Mode3D)
		{
			camera.ProcessKeyboard(RIGHT, deltaTime);
		}
		else
		{
			SpriteOffsetX += 128;
		}
	}

	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		OffsetX += 128;
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		OffsetX -= 128;
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_UP) == GLFW_PRESS)
		OffsetY += 128;
	if (glfwGetKey(Window.GetWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		OffsetY -= 128;
}