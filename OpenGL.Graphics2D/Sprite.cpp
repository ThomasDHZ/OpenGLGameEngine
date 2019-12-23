#include "Sprite.h"

Sprite::Sprite()
{
	SpriteTexture = Texture();
	Position = glm::vec2(0.0f);
}

Sprite::Sprite(Texture spriteTexture, glm::vec2 position)
{
	SpriteTexture = spriteTexture;
	Position = position;
}

Sprite::Sprite(char const* TexturePath, glm::vec2 position)
{
	SpriteTexture = Texture(TexturePath);
	Position = position;
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
}

void Sprite::SetPosition(glm::vec2 position)
{
	Position = position;
}

void Sprite::SetPosition(float x, float y)
{
	Position = glm::vec2(x,y);
}

void Sprite::ReleaseSprite()
{
	SpriteTexture.ReleaseTexture();
}

Sprite& Sprite::operator=(const Sprite& rhs)
{
	SpriteTexture = rhs.SpriteTexture;
	Position = rhs.Position;

	return *this;
}
