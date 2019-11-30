#include "Texture.h"
#include <glad\glad.h>
#include <gl\GL.h>
#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"
#include <FileSystem.h>
#include <iostream>
#include "ColorEnum.h"

Texture::Texture()
{
}

Texture::Texture(unsigned int Width, unsigned int Height)
{
	Color* NewTexture = new Color[Width * Height];

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NewTexture);

	delete[] NewTexture;
	NewTexture = nullptr;
}

Texture::Texture(char const* FilePath)
{
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true); 

	unsigned char* textureData = stbi_load(FileSystem::getPath(FilePath).c_str(), &Width, &Height, &ColorChannels, 0);
	if (textureData)
	{
		if (ColorChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		}
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(textureData);
}

Texture::~Texture()
{
}

void Texture::ReleaseTexture()
{
	glDeleteTextures(1, &TextureID);
}

Texture& Texture::operator=(const Texture& rhs)
{
	TextureID = rhs.TextureID;
	Width = rhs.Width;
	Height = rhs.Height;
	ColorChannels = rhs.ColorChannels;

	return* this;
}
