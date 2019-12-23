#pragma once
#include <glad/glad.h>
#include <cstddef>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "../OpenGL.Graphics3D/Texture.h"

class Layer2D
{
private:
	std::shared_ptr<Texture> LayerTexture;
public:
	Layer2D();
	Layer2D(unsigned int Width, unsigned int Height);
	~Layer2D();

	void Update(std::shared_ptr<Texture> AddTexture);
	std::shared_ptr<Texture> GetLayerTexture() { return LayerTexture; }

	Layer2D& operator=(const Layer2D& rhs);
};

