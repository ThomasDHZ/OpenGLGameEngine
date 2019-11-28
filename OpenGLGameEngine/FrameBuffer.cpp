#include "FrameBuffer.h"
#include "FileSystem.h"

FrameBuffer::FrameBuffer()
{
	OffsetX = 0;
	OffsetY = 0;

	FrameWidth = 0;
	FrameHeight = 0;

	cubeTexture = 0;
	quadVAO = 0;
	quadVBO = 0;

	FrameData = nullptr;
	data = nullptr;
}

FrameBuffer::FrameBuffer(Shader screenShader, unsigned int SCR_WIDTH, unsigned int SCR_HEIGHT)
{
	OffsetX = 0;
	OffsetY = 0;

	FrameWidth = SCR_WIDTH;
	FrameHeight = SCR_HEIGHT;

	FrameData = new Color[SCR_WIDTH * SCR_HEIGHT];

	float quadVertices[] =
	{
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	cubeTexture = loadTexture(FileSystem::getPath("Assets/alefgardfull4KTest.bmp").c_str());

	glGenTextures(1, &FrameTextureId);
	glBindTexture(GL_TEXTURE_2D, FrameTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FrameWidth, FrameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, FrameData);

	screenShader.use();
	screenShader.setInt("screenTexture", 0);

	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	delete[] data;
	delete[] FrameData;

	data = nullptr;
	FrameData = nullptr;

	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);
}

void FrameBuffer::SetPixel(int x, int y, Color color)
{
	FrameData[FrameWidth * y + x] = color;
}


void FrameBuffer::Update(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		OffsetY-= 1024;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		OffsetY += 1024;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		OffsetX -= 1024;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		OffsetX += 1024;
	}
}

void FrameBuffer::Render(Shader screenShader)
{
	//SetPixel(0, FrameHeight - 1, Color(rand() % 255, rand() % 255, rand() % 255));

	//for (int x = 0; x <= FrameWidth - 1; x++)
	//{
	//	for (int y = FrameHeight - 1; y >= 0; y--)
	//	{
	//		SetPixel(x, y, GetMapPixel(x + OffsetX, y + OffsetY));
	//	}
	//}

	//for (int x = 0; x <= FrameWidth - 1; x++)
	//{
	//	for (int y = FrameHeight - 1; y >= 0; y--)
	//	{
	//		SetPixel(x, y, GetMapPixel(x + OffsetX, y + OffsetY));
	//	}
	//}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FrameWidth, FrameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, FrameData);

	//glCopyImageSubData(cubeTexture, GL_TEXTURE_2D, 0, 0, 0, 0, FrameTextureId, GL_TEXTURE_2D, 0, 0, 0, 0, 50, 50, 1);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	screenShader.use();
	glBindVertexArray(quadVAO);
	glBindTexture(GL_TEXTURE_2D, FrameTextureId);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

unsigned int FrameBuffer::loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* tempData = stbi_load(path, &width, &height, &nrComponents, 0);
	
	
	data = new Color[width * height];
	for (int x = 0, temp = 0; x <= (width * height * 3) - 1; x+= 3, temp++)
	{
		data[temp] = Color(tempData[x], tempData[x + 1], tempData[x + 2]);
	}
	
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

	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;

	}

	return textureID;
}

Color FrameBuffer::GetMapPixel(int x, int y)
{
	return data[x * y];
}

Color FrameBuffer::GetPixel(int x, int y)
{
	return FrameData[x * y];
}

FrameBuffer& FrameBuffer::operator=(const FrameBuffer& rhs)
{
	cubeTexture = rhs.cubeTexture;
	quadVAO = rhs.quadVAO;
	quadVBO = rhs.quadVBO;

	return*this;
}