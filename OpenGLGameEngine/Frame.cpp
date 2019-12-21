#include "Frame.h"

Frame::Frame()
{
}

Frame::~Frame()
{
}

void Frame::InitializeFrameBuffer()
{
	float quadVertices[] =
	{
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &FrameBufferVAO);
	glGenBuffers(1, &FrameBufferVBO);
	glBindVertexArray(FrameBufferVAO);
	glBindBuffer(GL_ARRAY_BUFFER, FrameBufferVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &FrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);

	glGenTextures(1, &FrameTexture);
	glBindTexture(GL_TEXTURE_2D, FrameTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FrameTexture, 0);

	glGenRenderbuffers(1, &FrameBufferRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, FrameBufferRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, FrameBufferRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Frame::Update(unsigned int TextureID, unsigned int TextureID2)
{
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glDisable(GL_DEPTH_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(FrameBufferVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureID2);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Frame::CloseFrameBuffer()
{
	glDeleteFramebuffers(1, &FrameBufferID);
	glDeleteVertexArrays(1, &FrameBufferVAO);
	glDeleteBuffers(1, &FrameBufferVBO);
	glDeleteRenderbuffers(1, &FrameBufferRBO);
	glDeleteTextures(1, &FrameTexture);
}

Frame& Frame::operator=(const Frame& rhs)
{
	FrameBufferID = rhs.FrameBufferID;
	FrameBufferVAO = rhs.FrameBufferVAO;
	FrameBufferVBO = rhs.FrameBufferVBO;
	FrameBufferRBO = rhs.FrameBufferRBO;
	FrameTexture = rhs.FrameTexture;

	return*this;
}
