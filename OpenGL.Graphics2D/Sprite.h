#pragma once
#include "../OpenGL.Graphics3D/Texture.h"
#include <glm/glm.hpp>

class Sprite
{
private:
	Texture SpriteTexture;
	glm::vec2 Position;
public:
	Sprite();
	Sprite(Texture spriteTexture, glm::vec2 position);
	Sprite(char const* TexturePath, glm::vec2 position);
	~Sprite();

	void Update();
	void SetPosition(glm::vec2 position);
	void SetPosition(float x, float y);
	void ReleaseSprite();

	Texture GetSprite() { return SpriteTexture; }
	glm::vec2 GetPosition() { return Position; }

	Sprite& operator=(const Sprite& rhs);
};

