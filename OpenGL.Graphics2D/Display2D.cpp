#include "Display2D.h"

Display2D::Display2D()
{
}

Display2D::Display2D(unsigned int width, unsigned int height)
{
	Width = width;
	Height = height;
}

Display2D::~Display2D()
{
}

void Display2D::InitializeFrameBuffer()
{
	VertexCount = DisplayVertices.size();

	glGenVertexArrays(1, &FrameBufferVAO);
	glGenBuffers(1, &FrameBufferVBO);
	glBindVertexArray(FrameBufferVAO);

	glBindBuffer(GL_ARRAY_BUFFER, FrameBufferVBO);
	glBufferData(GL_ARRAY_BUFFER, VertexCount * sizeof(DisplayVertex), &DisplayVertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(DisplayVertexMap::Position);
	glEnableVertexAttribArray(DisplayVertexMap::TextureCoord);

	glVertexAttribPointer(DisplayVertexMap::Position, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribPointer(DisplayVertexMap::TextureCoord, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	glGenFramebuffers(1, &FrameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);

	glGenRenderbuffers(1, &FrameBufferRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, FrameBufferRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, FrameBufferRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Display2D::Update(unsigned int TextureID, std::vector<Layer2D>& LayerList) 
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(FrameBufferVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	for (int x = 0; x <= LayerList.size() - 1; x++)
	{
		glActiveTexture(GL_TEXTURE1 + x);
		glBindTexture(GL_TEXTURE_2D, LayerList[x].GetLayerTexture()->GetTextureID());
	}
	glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}

void Display2D::CloseFrameBuffer()
{
	glDeleteFramebuffers(1, &FrameBufferID);
	glDeleteVertexArrays(1, &FrameBufferVAO);
	glDeleteBuffers(1, &FrameBufferVBO);
	glDeleteRenderbuffers(1, &FrameBufferRBO);
}

Display2D& Display2D::operator=(const Display2D& rhs)
{
	FrameBufferID = rhs.FrameBufferID;
	FrameBufferVAO = rhs.FrameBufferVAO;
	FrameBufferVBO = rhs.FrameBufferVBO;
	FrameBufferRBO = rhs.FrameBufferRBO;
	VertexCount = rhs.VertexCount;

	return*this;
}
