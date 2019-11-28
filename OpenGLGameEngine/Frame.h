#pragma once
#include <glm/glm.hpp>
#include "ColorEnum.h"
#include <glad\glad.h>
#include <FileSystem.h>
#include <iostream>
#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"

enum ColorFormat
{
	RGB = 3,
	RGBA = 4
};

class Frame
{
private:
	unsigned int FrameTextureID;
	unsigned char* FrameTexture;
	unsigned Channels;
	//IVec2 FrameSize;

public:
	Frame();
	//Frame(IVec2 Size);
	~Frame();

	//void SetPixel(IVec2 pixelCoord, Color color);

	unsigned char* GetFrame();
	//unsigned char GetPixel(IVec2 pixelCoord);
	unsigned int GetFrameTextureID();
	unsigned int LoadTexture(const char* path);
	//IVec2 GetFrameSize();

};

