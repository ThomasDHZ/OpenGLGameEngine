#include "Frame.h"


Frame::Frame()
{
}

Frame::Frame(IVec2 Size)
{
	FrameSize = Size;

	int width, height, nrChannels;

	glGenTextures(1, &FrameTextureID);
	glBindTexture(GL_TEXTURE_2D, FrameTextureID); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP_TO_EDGE);

	FrameTexture = stbi_load(FileSystem::getPath("Assets/alefgardfull4KTest.bmp").c_str(), &width, &height, &nrChannels, 0);
	if (FrameTexture)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, FrameTexture);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(FrameTexture);
}

Frame::~Frame()
{
}

void Frame::SetPixel(IVec2 pixelCoord, Color color)
{
	FrameTexture[pixelCoord.x * pixelCoord.y] = color.r;
}

unsigned char* Frame::GetFrame()
{
	return FrameTexture;
}

unsigned char Frame::GetPixel(IVec2 pixelCoord)
{
	return FrameTexture[pixelCoord.x * pixelCoord.y];
}

unsigned int Frame::GetFrameTextureID()
{
	return FrameTextureID;
}

unsigned int Frame::LoadTexture(const char* path)
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

IVec2 Frame::GetFrameSize()
{
	return FrameSize;
}
