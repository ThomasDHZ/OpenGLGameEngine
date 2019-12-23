#include "BackGroundLayer.h"
#include <glad\glad.h>

BackGroundLayer::BackGroundLayer()
{
	OffsetX = 0;
	OffsetY = 0;
	DisplayTexture = nullptr;
}

BackGroundLayer::BackGroundLayer(unsigned int Width, unsigned int Height)
{
	OffsetX = 0;
	OffsetY = 0;
	DisplayTexture = std::make_shared<Texture>(Width, Height);
}

BackGroundLayer::~BackGroundLayer()
{
}

void BackGroundLayer::Update()
{
	float FinalOffsetY = BackGroundTexture->GetHeight() - DisplayTexture->GetHeight() + OffsetY;
	glCopyImageSubData(BackGroundTexture->GetTextureID(), GL_TEXTURE_2D, 0, OffsetX, FinalOffsetY, 0, DisplayTexture->GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, DisplayTexture->GetWidth(), DisplayTexture->GetHeight(), 1);
}

void BackGroundLayer::SetBackGourndTexture(std::shared_ptr<Texture> NewBackGroundTexture)
{
	BackGroundTexture = NewBackGroundTexture;
}

BackGroundLayer& BackGroundLayer::operator=(const BackGroundLayer& rhs)
{
	BackGroundTexture = rhs.BackGroundTexture;
	DisplayTexture = rhs.DisplayTexture;
	return *this;
}
