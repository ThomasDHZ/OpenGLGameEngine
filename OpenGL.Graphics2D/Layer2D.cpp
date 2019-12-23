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

void Layer2D::Update()
{
	glCopyImageSubData(SpriteTexture->GetSprite().GetTextureID(), GL_TEXTURE_2D, 0, 0, 0, 0, LayerTexture->GetTextureID(), GL_TEXTURE_2D, 0, SpriteTexture->GetPosition().x, SpriteTexture->GetPosition().y, 0, SpriteTexture->GetSprite().GetWidth(), SpriteTexture->GetSprite().GetHeight(), 1);
}

void Layer2D::AddSprite(std::shared_ptr<Sprite> AddSprite)
{
	SpriteTexture = AddSprite;
}

void Layer2D::ReleaseLayer()
{
	LayerTexture->ReleaseTexture();
}

Layer2D& Layer2D::operator=(const Layer2D& rhs)
{
	LayerTexture = rhs.LayerTexture;
	return *this;
}
