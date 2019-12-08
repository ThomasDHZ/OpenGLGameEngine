#pragma once
#include "Frame.h"
#include <GLFW\glfw3.h>

class FrameBuffer
{
private:
	unsigned int Width;
	unsigned int Height;
	unsigned int FrameBufferID;
	unsigned int FrameBufferVAO;
	unsigned int FrameBufferVBO;
	unsigned int FrameBufferRBO;
	unsigned int FrameTexture;
public:
	FrameBuffer();
	~FrameBuffer();

	void InitializeFrameBuffer(unsigned int Width, unsigned int Height);
	void FrameBufferStart();
	void FrameBufferEnd();
	void CloseFrameBuffer();
	FrameBuffer& operator=(const FrameBuffer& rhs);
};