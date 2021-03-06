#pragma once
#include "../OpenGL.Graphics3D/Texture.h"
#include <memory>

class BackGroundLayer
{
private:
	std::shared_ptr<Texture> BackGroundTexture;
	std::shared_ptr<Texture> DisplayTexture;
	int OffsetX;
	int OffsetY;

public:
	BackGroundLayer();
	BackGroundLayer(unsigned int Width, unsigned int Height);
	~BackGroundLayer();

	void Update();
	void SetBackGroundexture(std::shared_ptr<Texture> NewBackGroundTexture);
	void SetPosition(int X, int Y);
	void ReleaseTexture();

	std::shared_ptr<Texture> GetDisplayTexture() { return DisplayTexture; }
	BackGroundLayer& operator=(const BackGroundLayer& rhs);
};

