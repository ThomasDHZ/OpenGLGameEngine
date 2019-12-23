#include "Layer2D.h"

Layer2D::Layer2D()
{
	LayerTexture = nullptr;
}

Layer2D::Layer2D(unsigned int Width, unsigned int Height)
{
	LayerTexture = std::make_shared<Texture>(Width, Height);
}

Layer2D::~Layer2D()
{
}

void Layer2D::Update(std::shared_ptr<Texture> AddTexture)
{
	glCopyImageSubData(AddTexture->GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, LayerTexture->GetTextureID(), GL_TEXTURE_2D, 0, 2056, 0, 0, AddTexture->GetWidth(), AddTexture->GetHeight(), 1);
}

Layer2D& Layer2D::operator=(const Layer2D& rhs)
{
	LayerTexture = rhs.LayerTexture;
	return *this;
}
