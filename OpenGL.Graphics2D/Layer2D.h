#pragma once
#include <glad/glad.h>
#include <cstddef>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "../OpenGL.Graphics3D/Texture.h"
#include "Sprite.h"

class Layer2D
{
private:
	std::shared_ptr<Texture> LayerTexture;
	std::shared_ptr<Sprite> SpriteTexture;
public:
	Layer2D();
	Layer2D(unsigned int Width, unsigned int Height);
	~Layer2D();

	void Update();
	void AddSprite(std::shared_ptr<Sprite> AddSprite);
	void ReleaseLayer();

	std::shared_ptr<Texture> GetLayerTexture() { return LayerTexture; }

	Layer2D& operator=(const Layer2D& rhs);
};

