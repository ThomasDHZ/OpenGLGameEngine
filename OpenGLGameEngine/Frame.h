#pragma once
#include <glm/glm.hpp>
#include "ColorEnum.h"
#include <glad\glad.h>
#include <FileSystem.h>
#include <iostream>
#include "../../../../Desktop/New folder (5)/OpenGLEngine/Include/Soil/stb_image.h"

class Frame
{
private:
	unsigned int FrameBufferID;
	unsigned int FrameBufferVAO;
	unsigned int FrameBufferVBO;
	unsigned int FrameBufferRBO;
	unsigned int FrameTexture;
public:
	Frame();
	~Frame();

	void InitializeFrameBuffer();
	void Update(unsigned int TextureID, unsigned int TextureID2);
	void CloseFrameBuffer();
	Frame& operator=(const Frame& rhs);
};

